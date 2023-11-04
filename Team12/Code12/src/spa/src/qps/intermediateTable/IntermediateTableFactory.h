#pragma once

#include <functional>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "IntermediateTable.h"
#include "qps/common/Keywords.h"
#include "qps/intermediateTable/synonymRes/SynonymResFactory.h"

using std::set;

class IntermediateTableFactory {
 private:
  /**
   * Builds intermediate table without any WILDCARD columns
   * using using a vector of vectors of SynonymRes.
   * ! DOES NOT CHECK AND FILTER OUT WILDCARD COLUMNS
   */
  static IntermediateTable buildWithoutWildcardFilter(
      const vector<string> &colNames, TableDataType data);

 public:
  /**
   * Builds intermediate table without any WILDCARD columns
   */
  static IntermediateTable buildIntermediateTable(
      const string &firstColName, const string &secondColName,
      const vector<pair<string, string>> &data);

  /**
   * Builds intermediate table without any WILDCARD columns
   * and only one column
   * @tparam U    vector of SynonymRes references
   * @param  data take in vector of SynonymRes references
   */
  static IntermediateTable buildSingleColTable(
      const string &colName,
      const vector<std::reference_wrapper<SynonymRes>> &data) {
    // if data is empty, return empty table
    // even if columns are wildcard
    if (data.empty()) {
      return IntermediateTable::makeEmptyTable();
    }

    if (colName == WILDCARD_KEYWORD) {
      return IntermediateTable::makeWildcardTable();
    }

    vector<string> columnNames = {colName};
    TableDataType dataColumn = {};
    dataColumn.reserve(data.size());
    for (const std::reference_wrapper<SynonymRes> datum : data) {
      TableRowType row {std::move(datum)};
      dataColumn.emplace_back(std::move(row));
    }
    return IntermediateTable(columnNames, std::move(dataColumn));
  }

  /**
   * Builds intermediate table without any WILDCARD columns
   * and only one column AND one single row
   */
  static IntermediateTable buildIntermediateTable(
      const string &colName, std::reference_wrapper<SynonymRes> value);

  /**
   * Builds intermediate table without any WILDCARD columns
   * using using a vector of vectors of SynonymRes
   */
  static IntermediateTable buildIntermediateTable(
      const vector<string> &colNames, TableDataType data);

  static IntermediateTable buildEmptyIntermediateTable();

  static IntermediateTable buildWildcardIntermediateTable();
};
