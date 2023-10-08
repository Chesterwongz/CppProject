#pragma once

#include "IntermediateTable.h"

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "IntermediateTable.h"

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
   */
  static IntermediateTable buildSingleColTable(const string &firstColName,
                                               const vector<string> &data);

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

  /**
   * Builds intermediate table without any WILDCARD columns
   * using using a vector of vectors of SynonymRes
   */
  static IntermediateTable buildIntermediateTable(
      const vector<string> &colNames, const vector<vector<SynonymRes>> &data);

  static IntermediateTable buildEmptyIntermediateTable();

  static IntermediateTable buildWildcardIntermediateTable();
};
