#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "qps/common/Keywords.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/intermediateTable/synonymRes/SynonymRes.h"

using std::pair, std::unordered_map, std::unordered_set, std::string,
    std::vector, std::set, std::unique_ptr;

typedef vector<SynonymRes> TableRowType;
typedef vector<TableRowType> TableDataType;

class IntermediateTable {
 private:
  unordered_map<string, int> colNameToIndexMap = {};
  TableDataType tableData;
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

  /**
   * for initialising table from vector of vectors of SynonymRes
   * @param data data as vector of vectors
   */
  explicit IntermediateTable(const vector<string> &colNames,
                             TableDataType data);

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

 public:
  /**
   * @return the entire table's data with each cell converted to string
   */
  [[nodiscard]] vector<vector<string>> getDataAsStrings() const;

  /**
   * @param colNameVector vector of column names to retrieve
   * @return set of tuples string. elements in tuple delimited by space.
   *         e.g. { "a b c", "a b d", ... }
   */
  [[nodiscard]] unordered_set<string> getColumns(
      const vector<string> &colNameVector) const;

  /**
   * same as getColumns(const vector<string> &colNameVector), but allows
   * you to specify the specific attribute ref you want
   * retrieve
   */
  [[nodiscard]] unordered_set<string> getColumns(
      const vector<unique_ptr<SynonymArg>> &selectSynonyms) const;

  /**
   * Join a different intermediateTable into this
   * @param intermediateTable separate table to be joined into
   *                          this table
   */
  IntermediateTable join(const IntermediateTable &otherTable);

  /**
   * Join on specific column.
   * Cannot join if there are shared cols on top of the specified join col,
   * e.g. <a, b>, <a, b>, join on column a -> will have duplicate col b in res
   * @param otherTable
   * @param joinColThis  this table's colName and AttrRef pair
   * @param joinColOther other table's colName and AttrRef pair
   */
  IntermediateTable join(const IntermediateTable &otherTable,
                         const pair<string, AttrRef>& joinColThis,
                         const pair<string, AttrRef>& joinColOther);

  /**
   * @return vector of all column names
   */
  [[nodiscard]] vector<string> getColNames() const;

  /**
   * @return index of specified column
   */
  [[nodiscard]] int getColIndex(const string &colName) const;

  /**
   * checks if specified column name exists
   */
  [[nodiscard]] bool isColExists(const string &colName) const;

  /**
   * generic getter methods
   */
  [[nodiscard]] size_t getRowCount() const;
  [[nodiscard]] bool isTableEmpty() const;
  [[nodiscard]] bool isTableWildcard() const;
  [[nodiscard]] bool isTableEmptyAndNotWildcard() const;
  [[nodiscard]] TableDataType getTableData() const;
  void printTable() const;

  friend class IntermediateTableFactory;
};
