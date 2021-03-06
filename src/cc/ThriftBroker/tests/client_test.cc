/** -*- C++ -*-
 * Copyright (C) 2008  Luke Lu (Zvents, Inc.)
 *
 * This file is part of Hypertable.
 *
 * Hypertable is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or any later version.
 *
 * Hypertable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hypertable. If not, see <http://www.gnu.org/licenses/>
 */

#include "Common/Compat.h"
#include "Common/System.h"

#include <iostream>
#include <fstream>
#include "ThriftBroker/Client.h"
#include "ThriftBroker/gen-cpp/HqlService.h"
#include "ThriftBroker/ThriftHelper.h"

namespace Hypertable { namespace ThriftGen {

// Implement the If, so we don't miss any interface changes
struct BasicTest : HqlServiceIf {
  boost::shared_ptr<Thrift::Client> client;

  BasicTest() : client(new Thrift::Client("localhost", 38080)) { }

  void create_table(const std::string& name, const std::string& schema) {
    client->create_table(name, schema);
  }

  Scanner open_scanner(const std::string& name, const ScanSpec& scan_spec,
                       bool retry_table_not_found = true) {
    return client->open_scanner(name, scan_spec, retry_table_not_found);
  }

  void close_scanner(const Scanner scanner) {
    client->close_scanner(scanner);
  }

  void next_cells(std::vector<Cell> & _return, const Scanner scanner) {
    client->next_cells(_return, scanner);
  }

  void
  next_cells_as_arrays(std::vector<CellAsArray> & _return,
                       const Scanner scanner) {
    client->next_cells_as_arrays(_return, scanner);
  }

  void next_cells_serialized(CellsSerialized& _return,
                             const Scanner scanner) {
    client->next_cells_serialized(_return, scanner);
  }


  void next_row(std::vector<Cell> & _return, const Scanner scanner) {
    client->next_row(_return, scanner);
  }

  void
  next_row_as_arrays(std::vector<CellAsArray> & _return,
                     const Scanner scanner) {
    client->next_row_as_arrays(_return, scanner);
  }

  void
  get_row(std::vector<Cell> & _return, const std::string& name,
          const std::string& row) {
    client->get_row(_return, name, row);
  }

  void next_row_serialized(CellsSerialized& _return,
                           const Scanner scanner) {
    client->next_row_serialized(_return, scanner);
  }

  void
  get_row_as_arrays(std::vector<CellAsArray> & _return, const std::string& name,
                    const std::string& row) {
    client->get_row_as_arrays(_return, name, row);
  }

  void get_row_serialized(CellsSerialized& _return, const std::string& name,
                          const std::string& row) {
    client->get_row_serialized(_return, name, row);
  }

  void refresh_shared_mutator(const std::string &name, const MutateSpec &mutate_spec) {
    client->refresh_shared_mutator(name, mutate_spec);
  }

  void
  get_cell(Value& _return, const std::string& name, const std::string& row,
           const std::string& column) {
    client->get_cell(_return, name, row, column);
  }

  void
  get_cells(std::vector<Cell> & _return, const std::string& name,
            const ScanSpec& scan_spec) {
    client->get_cells(_return, name, scan_spec);
  }

  void
  get_cells_as_arrays(std::vector<CellAsArray> & _return,
                      const std::string& name, const ScanSpec& scan_spec) {
    client->get_cells_as_arrays(_return, name, scan_spec);
  }

  void
  get_cells_serialized(CellsSerialized& _return, const std::string& name,
                       const ScanSpec& scan_spec) {
    client->get_cells_serialized(_return, name, scan_spec);
  }

  void put_cell(const std::string &name, const MutateSpec &mutate_spec,
                const Cell &cell) {
    client->put_cell(name, mutate_spec, cell);
  }

  void put_cells(const std::string &name, const MutateSpec &mutate_spec,
                 const std::vector<Cell> & cells) {
    client->put_cells(name, mutate_spec, cells);
  }

  void put_cell_as_array(const std::string &name, const MutateSpec &mutate_spec,
                         const CellAsArray &cell) {
    client->put_cell_as_array(name, mutate_spec, cell);
  }

  void put_cells_as_arrays(const std::string &name, const MutateSpec &mutate_spec,
                           const std::vector<CellAsArray> & cells) {
    client->put_cells_as_arrays(name, mutate_spec, cells);
  }

  Mutator open_mutator(const std::string& name, int32_t flags,
                       int32_t flush_interval = 0) {
    return client->open_mutator(name, flags, flush_interval);
  }

  void close_mutator(const Mutator mutator, const bool flush) {
    client->close_mutator(mutator, flush);
  }

  void flush_mutator(const Mutator mutator) {
    client->flush_mutator(mutator);
  }

  void set_cell(const Mutator mutator, const Cell& cell) {
    client->set_cell(mutator, cell);
  }

  void set_cells(const Mutator mutator, const std::vector<Cell> & cells) {
    client->set_cells(mutator, cells);
  }

  void set_cell_as_array(const Mutator mutator, const CellAsArray& cell) {
    client->set_cell_as_array(mutator, cell);
  }

  void
  set_cells_as_arrays(const Mutator mutator,
                      const std::vector<CellAsArray> & cells) {
    client->set_cells_as_arrays(mutator, cells);
  }

  void
  set_cells_serialized(const Mutator mutator,
                       const CellsSerialized &cells,
                       bool flush) {
    client->set_cells_serialized(mutator, cells, flush);
  }

  bool exists_table(const std::string& name) {
    return client->exists_table(name);
  }

  int32_t get_table_id(const std::string& name) {
    return client->get_table_id(name);
  }

  void get_schema_str(std::string& _return, const std::string& name) {
    client->get_schema_str(_return, name);
  }

  void get_schema(Schema& _return, const std::string& name) {
    client->get_schema(_return, name);
  }

  void get_tables(std::vector<std::string> & _return) {
    client->get_tables(_return);
  }

  void get_table_splits(std::vector<TableSplit> & _return, const std::string& name) {
    client->get_table_splits(_return, name);
  }

  void drop_table(const std::string& name, const bool if_exists) {
    client->drop_table(name, if_exists);
  }

  void
  hql_exec(HqlResult& _return, const std::string &command, const bool noflush,
           const bool unbuffered) {
    client->hql_exec(_return, command, noflush, unbuffered);
  }

  void hql_query(HqlResult &ret, const std::string &command) {
    client->hql_query(ret, command);
  }

  void
  hql_exec2(HqlResult2& _return, const std::string &command, const bool noflush,
            const bool unbuffered) {
    client->hql_exec2(_return, command, noflush, unbuffered);
  }

  void hql_query2(HqlResult2 &ret, const std::string &command) {
    client->hql_query2(ret, command);
  }

  void run() {
    try {
      std::ostream &out = std::cout;
      test_hql(out);
      test_schema(out);
      test_scan(out);
      test_set();
      test_put();
      test_scan(out);
    }
    catch (ClientException &e) {
      std::cout << e << std::endl;
      exit(1);
    }
  }

  void test_hql(std::ostream &out) {
    HqlResult result;
    hql_query(result, "drop table if exists thrift_test");
    hql_query(result, "create table thrift_test ( col )");
    hql_query(result, "insert into thrift_test values"
                      "('2008-11-11 11:11:11', 'k1', 'col', 'v1'), "
                      "('2008-11-11 11:11:11', 'k2', 'col', 'v2'), "
                      "('2008-11-11 11:11:11', 'k3', 'col', 'v3')");
    hql_query(result, "select * from thrift_test");
    out << result << std::endl;

    HqlResult2 result2;
    hql_query2(result2, "select * from thrift_test");
    out << result2 << std::endl;
  }

  void test_scan(std::ostream &out) {
    ScanSpec ss;
    Scanner s = open_scanner("thrift_test", ss);
    std::vector<Cell> cells;

    do {
      next_cells(cells, s);
      foreach(const Cell &cell, cells)
        out << cell << std::endl;
    } while (cells.size());

    close_scanner(s);
    ss.cell_limit=1;
    ss.__isset.cell_limit = true;

    s = open_scanner("thrift_test", ss);
    do {
      next_cells(cells, s);
      foreach(const Cell &cell, cells)
        out << cell << std::endl;
    } while (cells.size());
  }

  void test_set() {
    std::vector<Cell> cells;

    Mutator m = open_mutator("thrift_test", 0);
    cells.push_back(make_cell("k4", "col", "cell_limit", "v-ignore-this-when-cell_limit=1",
                              "2008-11-11 22:22:22"));
    cells.push_back(make_cell("k4", "col", 0, "v4", "2008-11-11 22:22:23"));
    cells.push_back(make_cell("k5", "col", 0, "v5", "2008-11-11 22:22:22"));
    cells.push_back(make_cell("k2", "col", 0, "v2a", "2008-11-11 22:22:22"));
    cells.push_back(make_cell("k3", "col", 0, "", "2008-11-11 22:22:22", 0,
                              DELETE_ROW));
    set_cells(m, cells);
    close_mutator(m, true);
  }

  void test_schema(std::ostream &out) {
    Schema schema;
    get_schema(schema, "thrift_test");

    std::map<std::string, AccessGroup>::iterator ag_it = schema.access_groups.begin();
    out << "thrift test access groups:" << std::endl;
    while (ag_it != schema.access_groups.end()) {
      out << "\t" << ag_it->first << std::endl;
      ++ag_it;
    }
    std::map<std::string, ColumnFamily>::iterator cf_it = schema.column_families.begin();
    out << "thrift test column families:" << std::endl;
    while (cf_it != schema.column_families.end()) {
      out << "\t" << cf_it->first << std::endl;
      ++cf_it;
    }
  }

  void test_put() {
    std::vector<Cell> cells;
    MutateSpec mutate_spec;
    mutate_spec.appname = "test-cpp";
    mutate_spec.flush_interval = 1000;

    cells.push_back(make_cell("put1", "col", 0, "v1", "2008-11-11 22:22:22"));
    cells.push_back(make_cell("put2", "col", 0, "this_will_be_deleted", "2008-11-11 22:22:22"));
    put_cells("thrift_test", mutate_spec, cells);
    cells.clear();
    cells.push_back(make_cell("put1", "no_such_col", 0, "v1", "2008-11-11 22:22:22"));
    cells.push_back(make_cell("put2", "col", 0, "", "2008-11-11 22:22:23", 0,
                              DELETE_ROW));
    refresh_shared_mutator("thrift_test", mutate_spec);
    put_cells("thrift_test", mutate_spec, cells);
    sleep(2);
  }

};

}} // namespace Hypertable::Thrift

int main() {
  Hypertable::ThriftGen::BasicTest test;
  test.run();
}
