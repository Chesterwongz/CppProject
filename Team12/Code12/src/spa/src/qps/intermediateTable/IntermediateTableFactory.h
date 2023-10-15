#pragma once

#include <functional>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "IntermediateTable.h"

using std::set;

class IntermediateTableFactory {
 private:
  /**
   * Helper function for building intermediate tables from vector data
   * @tparam T            either unique_ptr<SynonymArg> or string
   * @param converterFunc function to convert T into unique_ptr<SynonymArg>
   */
  template <typename T>
  static IntermediateTable tableBuilderHelper(
      const vector<string> &colNames, const vector<vector<T>> &data,
      std::function<unique_ptr<SynonymRes>(const T &)> converterFunc) {
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
    vector<vector<unique_ptr<SynonymRes>>> dataWithoutWildcardColumns = {};
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
        dataWithoutWildcardColumns.at(rowIndex).push_back(
            std::move(converterFunc(std::move(data.at(rowIndex).at(colIndex)))));
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
      vector<pair<string, string>> data);

  /**
   * Builds intermediate table without any WILDCARD columns
   */
  static IntermediateTable buildIntermediateTable(
      const vector<string> &colNames, vector<vector<string>> data);

  /**
   * Builds intermediate table without any WILDCARD columns
   * and only one column
   */
  static IntermediateTable buildSingleColTable(const string &firstColName,
                                               vector<string> data);

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
      const vector<string> &colNames,
      vector<vector<unique_ptr<SynonymRes>>> data);

  static IntermediateTable buildEmptyIntermediateTable();

  static IntermediateTable buildWildcardIntermediateTable();
};
