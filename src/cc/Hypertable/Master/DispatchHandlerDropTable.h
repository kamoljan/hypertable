/** -*- c++ -*-
 * Copyright (C) 2008 Doug Judd (Zvents, Inc.)
 *
 * This file is part of Hypertable.
 *
 * Hypertable is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2 of the
 * License, or any later version.
 *
 * Hypertable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef HYPERTABLE_DISPATCHHANDLERDROPTABLE_H
#define HYPERTABLE_DISPATCHHANDLERDROPTABLE_H

#include "AsyncComm/Comm.h"
#include "AsyncComm/DispatchHandler.h"
#include "AsyncComm/Event.h"

#include "Common/SockAddrMap.h"

#include "Hypertable/Lib/RangeServerClient.h"

namespace Hypertable {

  /**
   * This class is a DispatchHandler class that is used for collecting
   * asynchronous drop table requests.
   */
  class DispatchHandlerDropTable : public DispatchHandler {

  public:

    struct ErrorResult {
      CommAddress addr;
      int error;
      std::string msg;
    };

    /**
     * Constructor.
     */
    DispatchHandlerDropTable(const TableIdentifier &table, Comm *comm);

    /**
     * Adds
     */
    void add(const CommAddress &addr);

    /**
     * Dispatch method.  This gets called by the AsyncComm layer
     * when an event occurs in response to a previously sent
     * request that was supplied with this dispatch handler.
     *
     * @param event_ptr shared pointer to event object
     */
    virtual void handle(EventPtr &event_ptr);

    bool wait_for_completion();

    void get_errors(std::vector<ErrorResult> &errors);

  private:
    Mutex              m_mutex;
    boost::condition   m_cond;
    int                m_outstanding;
    RangeServerClient  m_client;
    TableIdentifier    m_table;
    std::string        m_table_name;
    std::vector<ErrorResult> m_errors;
  };
}


#endif // HYPERTABLE_DISPATCHHANDLERDROPTABLE_H
