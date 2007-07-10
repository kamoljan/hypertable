/**
 * Copyright 2007 Doug Judd (Zvents, Inc.)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at 
 *
 * http://www.apache.org/licenses/LICENSE-2.0 
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


package org.hypertable.HdfsBroker;

import org.apache.hadoop.fs.Path;

import java.nio.ByteBuffer;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.net.ProtocolException;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.logging.Logger;
import java.util.logging.Level;

import org.hypertable.AsyncComm.Comm;
import org.hypertable.AsyncComm.CommBuf;
import org.hypertable.AsyncComm.Event;
import org.hypertable.AsyncComm.Message;
import org.hypertable.AsyncComm.MessageBuilderSimple;

import org.hypertable.Common.Error;


public class RequestOpen extends Request {

    public RequestOpen(OpenFileMap ofmap, Event event) throws ProtocolException {
	super(ofmap, event);

	if (event.msg.buf.remaining() < 4)
	    throw new ProtocolException("Truncated message");

	mBufferSize = event.msg.buf.getInt();

	if ((mFilename = CommBuf.DecodeString(event.msg.buf)) == null)
	    throw new ProtocolException("Filename not properly encoded in request packet");

	mFileId = msUniqueId.incrementAndGet();

	mOpenFileData = mOpenFileMap.Create(mFileId);
    }

    public void run() {
	int error;
	CommBuf cbuf = null;

	try {

	    if (Global.verbose)
		log.info("Opening file '" + mFilename + "' handle = " + mFileId);

	    if (mBufferSize == 0)
		mOpenFileData.is = Global.fileSystem.open(new Path(mFilename));
	    else
		mOpenFileData.is = Global.fileSystem.open(new Path(mFilename));

	    cbuf = new CommBuf(mOpenFileData.mbuilder.HeaderLength() + 10);
	    cbuf.PrependInt(mFileId);
	    cbuf.PrependShort(Protocol.COMMAND_OPEN);
	    cbuf.PrependInt(Error.OK);

	    // Encapsulate with Comm message response header
	    mOpenFileData.mbuilder.LoadFromMessage(mEvent.msg);
	    mOpenFileData.mbuilder.Encapsulate(cbuf);
	    
	    if ((error = Global.comm.SendResponse(mEvent.addr, cbuf)) != Error.OK)
		log.log(Level.SEVERE, "Comm.SendResponse returned " + Error.GetText(error));
	    return;
	}
	catch (FileNotFoundException e) {
	    log.log(Level.WARNING, "File not found: " + mFilename);
	    cbuf = Global.protocol.CreateErrorMessage(Protocol.COMMAND_OPEN, Error.HDFSBROKER_FILE_NOT_FOUND,
						      e.getMessage(), mOpenFileData.mbuilder.HeaderLength());
	}
	catch (IOException e) {
	    e.printStackTrace();
	    cbuf = Global.protocol.CreateErrorMessage(Protocol.COMMAND_OPEN, Error.HDFSBROKER_IO_ERROR,
						      e.getMessage(), mOpenFileData.mbuilder.HeaderLength());
	}

	// Encapsulate with Comm message response header
	mOpenFileData.mbuilder.LoadFromMessage(mEvent.msg);
	mOpenFileData.mbuilder.Encapsulate(cbuf);

	if ((error = Global.comm.SendResponse(mEvent.addr, cbuf)) != Error.OK)
	    log.log(Level.SEVERE, "Comm.SendResponse returned " + Error.GetText(error));
	
    }

    private String        mFilename;
    private int           mBufferSize;
}
