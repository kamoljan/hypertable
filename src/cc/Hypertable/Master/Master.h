/** -*- c++ -*-
 * Copyright (C) 2009 Doug Judd (Zvents, Inc.)
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

#ifndef HYPERTABLE_MASTER_H
#define HYPERTABLE_MASTER_H

extern "C" {
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
}

#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

#include "Common/Thread.h"
#include "Common/ReferenceCount.h"
#include "Common/SockAddrMap.h"
#include "Common/String.h"
#include "Common/StringExt.h"
#include "Common/Properties.h"
#include "Common/Filesystem.h"

#include "AsyncComm/ApplicationQueue.h"
#include "AsyncComm/Comm.h"
#include "AsyncComm/ConnectionManager.h"
#include "AsyncComm/Event.h"
#include "AsyncComm/ResponseCallback.h"

#include "Hyperspace/Session.h"

#include "Hypertable/Lib/Table.h"
#include "Hypertable/Lib/Types.h"
#include "Hypertable/Lib/Schema.h"
#include "Hypertable/Lib/StatsV0.h"

#include "HyperspaceSessionHandler.h"
#include "RangeServerState.h"
#include "ResponseCallbackGetSchema.h"
#include "ResponseCallbackRegisterServer.h"
#include "MasterGc.h"

namespace Hypertable {
  using namespace Hyperspace;

  class Master : public ReferenceCount {
  public:
    Master(PropertiesPtr &, ConnectionManagerPtr &, ApplicationQueuePtr &);
    ~Master();

    void create_table(ResponseCallback *cb, const char *tablename,
                      const char *schemastr);
    void alter_table(ResponseCallback *cb, const char *tablename,
                      const char *schemastr);
    void get_schema(ResponseCallbackGetSchema *cb, const char *tablename);
    void register_server(ResponseCallbackRegisterServer *cb, String &location,
                         const InetAddr &addr);
    void report_split(ResponseCallback *cb, const TableIdentifier &table,
                      const RangeSpec &range, const char *transfer_log_dir,
                      uint64_t soft_limit);
    void drop_table(ResponseCallback *cb, const char *table_name,
                    bool if_exists);
    void close(ResponseCallback *cb);
    void shutdown(ResponseCallback *cb);

    void server_joined(const String &location);
    void server_left(const String &location);

    bool handle_disconnect(struct sockaddr_in addr, String &location);

    void do_maintenance();

    void join();

  protected:
    void create_table(const char *tablename, const char *schemastr);

  private:
    bool initialize();
    void scan_servers_directory();
    bool create_hyperspace_dir(const String &dir);
    void wait_for_root_metadata_server();
    void get_statistics(bool snapshot);
    void refresh_table_id_mapping();

    Mutex        m_mutex;
    PropertiesPtr m_props_ptr;
    ConnectionManagerPtr m_conn_manager_ptr;
    ApplicationQueuePtr m_app_queue_ptr;
    bool m_verbose;
    Hyperspace::SessionPtr m_hyperspace_ptr;
    Filesystem *m_dfs_client;
    atomic_t m_last_table_id;
    uint32_t m_next_server_id;
    HyperspaceSessionHandler m_hyperspace_session_handler;
    uint64_t m_master_file_handle;
    uint64_t m_servers_dir_handle;
    LockSequencer m_master_file_sequencer;
    HandleCallbackPtr m_servers_dir_callback_ptr;
    TablePtr m_metadata_table_ptr;
    uint64_t m_max_range_bytes;

    /** temporary vairables **/
    bool m_initialized;
    Mutex m_root_server_mutex;
    boost::condition  m_root_server_cond;
    bool m_root_server_connected;
    String m_root_server_location;
    struct sockaddr_in m_root_server_addr;

    typedef hash_map<QualifiedRangeSpec, String,
                     QualifiedRangeHash, QualifiedRangeEqual> RangeToLocationMap;

    typedef map<String, bool> RangeServerStatsStateMap;

    RangeServerStatsStateMap m_server_stats_state_map;
    RangeServerStatsMap m_server_stats_map;
    TableStatsSnapshotBuffer m_table_stats_buffer;
    RangeServerHLStatsSnapshotBuffer m_range_server_stats_buffer;
    Mutex m_stats_mutex;
    bool m_get_stats_outstanding;
    map<String, uint32_t> m_table_names_to_ids;
    map<uint32_t, String> m_table_ids_to_names;

    // protected by m_mutex
    SockAddrMap<String> m_addr_map;
    RangeServerStateMap m_server_map;
    RangeServerStateMap::iterator  m_server_map_iter;
    boost::condition  m_no_servers_cond;
    RangeToLocationMap m_range_to_location_map;

    ThreadGroup m_threads;
    static const uint32_t MAX_ALTER_TABLE_RETRIES = 3;
    static String ms_monitoring_dir;
  };

  typedef intrusive_ptr<Master> MasterPtr;

} // namespace Hypertable

#endif // HYPERTABLE_MASTER_H
