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


#ifndef HYPERTABLE_PROTOCOL_H
#define HYPERTABLE_PROTOCOL_H

#include <string>

namespace hypertable {
  
  class CommBuf;
  class Event;

  class Protocol {

  public:

    virtual ~Protocol() { return; }

    static int32_t ResponseCode(Event *event);

    std::string StringFormatMessage(Event *event);

    CommBuf *CreateErrorMessage(uint16_t command, int error, const char *msg, int extraSpace);

    virtual const char *CommandText(short command) = 0;

  };

}

#endif // HYPERTABLE_PROTOCOL_H
