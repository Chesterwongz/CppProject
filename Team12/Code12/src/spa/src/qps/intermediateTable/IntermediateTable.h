#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include "qps/intermediateTable/synonymRes/SynonymRes.h"

using std::pair, std::unordered_map, std::string, std::vector, std::set;
class IntermediateTable {
 private:
  unordered_map<string, int> colNameToIndexMap = {};
  vector<vector<SynonymRes>> tableData;
  vector<string> colNames = {};
  int currentColCount = 0;
  bool isWildcard = false;
  bool isEmpty;

  /**
   * add an empty column to the table
   * @param newColName takes in name of new column
   * @return index of new column
   */
  int createNewCol(const string &newColName);

  /**
   * for initialising table empty or wildcard tables
   */
  explicit IntermediateTable(bool isTableWildcard);

 public:
  /**
   * for initialising table from vector of pairs.
   * only can initialise 2 columns.
   * @param data data as vector of pairs
   */
  explicit IntermediateTable(const string &firstColName,
                             const string &secondColName,
                             const vector<pair<string, string>> &data);

  /**
   * for initialising table from vector of vectors
   * @param data data as vector of vectors
   */
  explicit IntermediateTable(const vector<string> &colNames,
                             const vector<vector<string>> &data);

  /**
   * Wildcard table * ANY = ANY
   * !!! Wildcard tables are empty by definition !!!
   * @return Wildcard table
   */
  static IntermediateTable makeWildcardTable();

  /**
   * Empty table * ANY = Empty table
   * @return Empty table
   */
  static IntermediateTable makeEmptyTable();

  /**
   * @return the entire table's data
   */
  vector<vector<string>> getData();

  /**
   * @param colNameVector vector of column names to retrieve
   * @return set of tuples string. elements in tuple delimited by space.
   *         e.g. { "a b c", "a b d", ... }
   */
  set<string> getColumns(const vector<string> &colNameVector);

  /**
   * same as getColumns(const vector<string> &colNameVector), but allows
   * you to specify the specific attribute ref you want
   * @param colNameAndAttrRefVector vector of <column names, attrRef> pairs to
   * retrieve
   */
  set<string> getColumns(
      const vector<pair<string, AttrRef>> &colNameAndAttrRefVector);

  /**
   * Join a different intermediateTable into this
   * @param intermediateTable separate table to be joined into
   *                          this table
   */
  IntermediateTable join(const IntermediateTable &intermediateTable);

  /**
   * @return vector of all column names
   */
  vector<string> getColNames();

  /**
   * @return index of specified column
   */
  int getColIndex(const string &colName);

  /**
   * checks if specified column name exists
   */
  bool isColExists(const string &colName);

  /**
   * generic getter methods
   */
  int getRowCount();
  bool isTableEmpty() const;
  bool isTableWildcard() const;
  bool isTableEmptyAndNotWildcard() const;
  void printTable();
};
