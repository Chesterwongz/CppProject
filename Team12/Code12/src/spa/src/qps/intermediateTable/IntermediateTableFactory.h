#pragma once

#include "IntermediateTable.h"

#include <string>
#include <utility>
#include <vector>

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
   */
  static IntermediateTable buildSingleColTable(const string &firstColName,
                                               const vector<string> &data);

  /**
   * Builds intermediate table without any WILDCARD columns
   * and only one column AND one single row
   */
  static IntermediateTable buildIntermediateTable(const string &colName,
                                                  const string &value);

  static IntermediateTable buildEmptyIntermediateTable();

  static IntermediateTable buildWildcardIntermediateTable();
};
