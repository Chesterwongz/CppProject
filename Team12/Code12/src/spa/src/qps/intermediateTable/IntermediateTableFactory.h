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
   * Helper function for building intermediate tables from vector data
   * @tparam T            either SynonymArg or string
   */
  template <typename T>
  static IntermediateTable tableBuilderHelper(const vector<string> &colNames,
                                              vector<vector<T>> data) {
    // if data is empty, return empty table
    // even if columns are wildcard
    if (data.empty()) {
      return IntermediateTable::makeEmptyTable();
    }

    bool isAllWildcardColumns = std::count(colNames.begin(), colNames.end(),
                                           WILDCARD_KEYWORD) == colNames.size();
    if (isAllWildcardColumns) {
      return IntermediateTable::makeWildcardTable();
    }

    vector<string> columnNamesWithoutWildcard = {};
    TableDataType dataWithoutWildcardColumns = {};
    dataWithoutWildcardColumns.reserve(data.size());
    // add empty vector for each row
    for ([[maybe_unused]] const vector<T> &row : data) {
      dataWithoutWildcardColumns.emplace_back();
    }
    for (int colIndex = 0; colIndex < colNames.size(); colIndex++) {
      const string &colName = colNames.at(colIndex);
      if (colName == WILDCARD_KEYWORD) {
        // ignore wildcard columns
        continue;
      }
      columnNamesWithoutWildcard.push_back(colName);
      for (int rowIndex = 0; rowIndex < data.size(); rowIndex++) {
        // implicitly calls SynonymRes constructor if datum is string
        dataWithoutWildcardColumns.at(rowIndex).emplace_back(
            std::move(data.at(rowIndex).at(colIndex)));
      }
    }
    return IntermediateTable(columnNamesWithoutWildcard,
                             dataWithoutWildcardColumns);
  }

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
      const vector<string> &colNames, vector<vector<string>> data);

  /**
   * Builds intermediate table without any WILDCARD columns
   * and only one column
   * @tparam U    vector/unordered_set/set of strings/SynonymRes
   * @param  data take in vector/unordered_set/set of strings/SynonymRes
   */
  template <typename U>
  static IntermediateTable buildSingleColTable(
      const string &colName, const U &data) {
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
    for (auto &datum : data) {
      TableRowType row{};
      // implicitly calls SynonymRes constructor if datum is string
      row.emplace_back(std::move(datum));
      dataColumn.emplace_back(std::move(row));
    }
    return IntermediateTable(columnNames, dataColumn);
  }

  /**
   * Builds intermediate table without any WILDCARD columns
   * and only one column
   */
  static IntermediateTable buildIntermediateTable(const string &firstColName,
                                                  set<string> data);

  /**
   * Builds intermediate table without any WILDCARD columns
   * and only one column AND one single row
   */
  static IntermediateTable buildIntermediateTable(const string &colName,
                                                  string value);

  /**
   * Builds intermediate table without any WILDCARD columns
   * using using a vector of vectors of SynonymRes
   */
  static IntermediateTable buildIntermediateTable(
      const vector<string> &colNames, TableDataType data);

  static IntermediateTable buildEmptyIntermediateTable();

  static IntermediateTable buildWildcardIntermediateTable();
};
