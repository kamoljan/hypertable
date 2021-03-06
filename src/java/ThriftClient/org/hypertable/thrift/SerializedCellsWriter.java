/**
 * Copyright (C) 2010  Doug Judd (Hypertable, Inc.)
 *
 * This file is distributed under the Apache Software License
 * (http://www.apache.org/licenses/)
 */


package org.hypertable.thrift;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class SerializedCellsWriter {

  public SerializedCellsWriter(int size) {
    mBuffer = ByteBuffer.allocate(size);
    mBuffer.order(ByteOrder.LITTLE_ENDIAN);
    mGrow=false;
  }

  public SerializedCellsWriter(int size, boolean grow) {
    mBuffer = ByteBuffer.allocate(size);
    mBuffer.order(ByteOrder.LITTLE_ENDIAN);
    mGrow = grow;
  }

  /**
   * Add a byte array that has been created & finalized by SerializedCellsWriter.array()
   * Assumes that the last byte in the parameter is a flag and adds all but the
   * last byte.
   *
   * @param serialized_cells byte array that must have been generated by SerializedCellsWriter.array
   * @return true if cells were added
   */
  public boolean add_serialized_cell_array(byte [] serialized_cells) {
    int length = serialized_cells.length - 1;

    // need to leave room for the termination byte
    if (length >= mBuffer.remaining()) {
      if (mBuffer.position() > 0) {
        if (!mGrow) // dont grow this buffer
          return false;
        else {
          // grow
          ByteBuffer newBuffer = ByteBuffer.allocate(((mBuffer.capacity()+length)*3)/2);
          newBuffer.order(ByteOrder.LITTLE_ENDIAN);
          newBuffer.put(mBuffer.array(), 0, mBuffer.position());
          mBuffer = newBuffer;
        }
      }
    }
    mBuffer.put(serialized_cells, 0 , length);
    return true;
  }

  public boolean add(String row, String column_family, String column_qualifier, long timestamp, ByteBuffer value) {
    byte [] row_bytes = row.getBytes();
    byte [] column_family_bytes = column_family.getBytes();
    byte [] column_qualifier_bytes = column_qualifier.getBytes();
    return add(row_bytes, 0, row_bytes.length,
               column_family_bytes, 0, column_family_bytes.length,
               column_qualifier_bytes, 0, column_qualifier_bytes.length,
               timestamp, value.array(), value.arrayOffset(), value.limit());
  }

  public boolean add(ByteBuffer row, ByteBuffer column_family, ByteBuffer column_qualifier, long timestamp, ByteBuffer value) {
    return add(row.array(), row.arrayOffset(), row.limit(),
               column_family.array(), column_family.arrayOffset(), column_family.limit(),
               column_qualifier.array(), column_qualifier.arrayOffset(), column_qualifier.limit(),
               timestamp, value.array(), value.arrayOffset(), value.limit());
  }

  public boolean add(byte [] row, int row_offset, int row_length,
                     byte [] column_family, int column_family_offset, int column_family_length,
                     byte [] column_qualifier, int column_qualifier_offset, int column_qualifier_length,
                     long timestamp,
                     byte [] value, int value_offset, int value_length) {
    int length = 8 + row_length + column_family_length + column_qualifier_length + value_length;
    byte flag = 0;

    if (timestamp == SerializedCellsFlag.AUTO_ASSIGN)
      flag |= SerializedCellsFlag.AUTO_TIMESTAMP;
    else if (timestamp != SerializedCellsFlag.NULL) {
      flag |= SerializedCellsFlag.HAVE_TIMESTAMP;
      length += 8;
    }

    // need to leave room for the termination byte
    if (length >= mBuffer.remaining()) {
      if (mBuffer.position() > 0) {
        if (!mGrow) // dont grow this buffer
          return false;
        else {

          // grow
          ByteBuffer newBuffer = ByteBuffer.allocate(((mBuffer.capacity()+length)*3)/2);
          newBuffer.order(ByteOrder.LITTLE_ENDIAN);
          newBuffer.put(mBuffer.array(), 0, mBuffer.position());
          mBuffer = newBuffer;
        }
      }
      else {
        mBuffer = ByteBuffer.allocate(length+1);
        mBuffer.order(ByteOrder.LITTLE_ENDIAN);
      }
    }

    // flag byte
    mBuffer.put(flag);


    // timestamp
    if ((flag & SerializedCellsFlag.HAVE_TIMESTAMP) != 0)
      mBuffer.putLong(timestamp);

    if ((flag & SerializedCellsFlag.HAVE_REVISION) != 0 &&
        (flag & SerializedCellsFlag.REV_IS_TS) == 0)
      mBuffer.putLong((long)0);

    // row
    mBuffer.put(row, row_offset, row_length);
    mBuffer.put((byte)0);

    // column family
    mBuffer.put(column_family, column_family_offset, column_family_length);
    mBuffer.put((byte)0);

    // column qualifier
    mBuffer.put(column_qualifier, column_qualifier_offset, column_qualifier_length);
    mBuffer.put((byte)0);

    mBuffer.putInt(value_length);  // fix me: should be zero-compressed
    mBuffer.put(value, value_offset, value_length);

    return true;
  }

  public void finalize(byte flag) {
    mBuffer.put((byte)(SerializedCellsFlag.EOB | flag));
    mBuffer.flip();
    mFinalized = true;
  }

  public byte [] array() {
    if (!mFinalized)
      finalize(SerializedCellsFlag.EOB);
    byte [] rbuf = new byte [ mBuffer.limit() ];
    mBuffer.get(rbuf);
    mBuffer.rewind();
    return rbuf;
  }

  public boolean isEmpty() {
    return mBuffer.position() == 0;
  }

  public void clear() {
    mBuffer.clear();
    mFinalized = false;
  }

  public int capacity() {
    return mBuffer.capacity();
  }

  private ByteBuffer mBuffer;
  private boolean mFinalized = false;
  private boolean mGrow = false;
}
