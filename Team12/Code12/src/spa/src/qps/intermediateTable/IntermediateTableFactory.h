#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "IntermediateTable.h"
#include "qps/common/Keywords.h"

using std::set;

class IntermediateTableFactory {
 public:
  /**
   * Builds intermediate table without any WILDCARD columns
   */
  static IntermediateTable buildIntermediateTable(
      const string &firstColName, const string &secondColName,
      const vector<pair<string, string>> &data);

  /**
   * Builds intermediate table without any WILDCARD columns
   */
  static IntermediateTable buildIntermediateTable(
      const vector<string> &colNames, const vector<vector<string>> &data);

  /**
   * Builds intermediate table without any WILDCARD columns
   * and only one column
   * @tparam VectorOrSetOfStrings vector/unordered_set/set of strings
   * @param  data                 take in vector/unordered_set/set of strings
   */
  template <typename VectorOrSetOfStrings>
  static IntermediateTable buildSingleColTable(
      const string &colName, const VectorOrSetOfStrings &data) {
    // if data is empty, return empty table
    // even if columns are wildcard
    if (data.empty()) {
      return IntermediateTable::makeEmptyTable();
    }

    if (colName == WILDCARD_KEYWORD) {
      return IntermediateTable::makeWildcardTable();
    }

    vector<string> columnNames = {colName};
    vector<vector<string>> dataColumn = {};
    dataColumn.reserve(data.size());
    for (const auto &rowIndex : data) {
      vector<string> elementToAdd = {rowIndex};
      dataColumn.push_back(elementToAdd);
    }
    return IntermediateTable(columnNames, dataColumn);
  }

  /**
   * Builds intermediate table without any WILDCARD columns
   * and only one column
   */
  static IntermediateTable buildIntermediateTable(const string &firstColName,
                                                  const set<string> &data);

  /**
   * Builds intermediate table without any WILDCARD columns
   * and only one column AND one single row
   */
  static IntermediateTable buildIntermediateTable(const string &colName,
                                                  const string &value);

  static IntermediateTable buildEmptyIntermediateTable();

  static IntermediateTable buildWildcardIntermediateTable();
};
