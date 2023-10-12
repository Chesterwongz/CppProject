#include "IntermediateTableUtils.h"

#include <stdexcept>

#include "common/utils/VectorUtils.h"

vector<string> getSharedColNames(IntermediateTable table1,
                                 IntermediateTable table2) {
  vector<string> tableNames1 = table1.getColNames();
  vector<string> tableNames2 = table2.getColNames();
  return intersectVectors(tableNames1, tableNames2);
}

pair<vector<int>, vector<int>> getSharedColIndexes(IntermediateTable table1,
                                                   IntermediateTable table2) {
  vector<string> sharedColNames = getSharedColNames(table1, table2);
  vector<int> table1Indexes = {};
  std::transform(sharedColNames.begin(), sharedColNames.end(),
                 std::back_inserter(table1Indexes),
                 [&table1](const string &colName) -> int {
                   return table1.getColIndex(colName);
                 });

  vector<int> table2Indexes = {};
  std::transform(sharedColNames.begin(), sharedColNames.end(),
                 std::back_inserter(table2Indexes),
                 [&table2](const string &colName) -> int {
                   return table2.getColIndex(colName);
                 });

  return {table1Indexes, table2Indexes};
}

IntermediateTable getCrossProduct(IntermediateTable table1,
                                  IntermediateTable table2) {
  if (!getSharedColNames(table1, table2).empty()) {
    throw std::runtime_error(
        "Cross product not supported for tables with common columns");
  }
  vector<string> resColumns =
      concatColNames(table1.getColNames(), table2.getColNames());
  vector<vector<unique_ptr<SynonymRes>>> resData = {};
  vector<vector<unique_ptr<SynonymRes>>> table1Data = table1.getTableData();
  vector<vector<unique_ptr<SynonymRes>>> table2Data = table2.getTableData();

  for (const vector<unique_ptr<SynonymRes>> &row1 : table1.getTableData()) {
    for (const vector<unique_ptr<SynonymRes>> &row2 : table2.getTableData()) {
      resData.push_back(concatRow(row1, row2));
    }
  }
  return IntermediateTable(resColumns, resData);
}

IntermediateTable getInnerJoin(
    const pair<vector<int>, vector<int>> &sharedColumnIndexes,
    IntermediateTable table1, IntermediateTable table2) {
  vector<string> resColNames =
      concatColNames(table1.getColNames(), table2.getColNames());
  vector<vector<unique_ptr<SynonymRes>>> resData = {};
  vector<vector<unique_ptr<SynonymRes>>> table1Data = table1.getTableData();
  vector<vector<unique_ptr<SynonymRes>>> table2Data = table2.getTableData();
  vector<int> table1SharedColIndexes = sharedColumnIndexes.first;
  vector<int> table2SharedColIndexes = sharedColumnIndexes.second;
  for (auto &table1Row : table1Data) {
    for (auto &table2Row : table2Data) {
      bool isJoin = true;
      for (int i = 0; i < table1SharedColIndexes.size(); i++) {
        // check that for this particular row,
        // all elements in shared cols of table 1
        // matches with all elements in shared cols of table 2
        int table1ColIndex = table1SharedColIndexes.at(i);
        int table2ColIndex = table2SharedColIndexes.at(i);
        // todo fix comparison for unique ptr
        if (table1Row.at(table1ColIndex) != table2Row.at(table2ColIndex)) {
          isJoin = false;
          break;
        }
      }
      if (isJoin) {
        resData.push_back(concatRow(table1Row, table2Row));
      }
    }
  }

  // sort indexes of table1Cols that were shared
  // from largest to smallest
  sort(table1SharedColIndexes.rbegin(), table1SharedColIndexes.rend());
  // remove extra shared columns from table 1
  // from largest to smallest index
  for (int index : table1SharedColIndexes) {
    resColNames.erase(resColNames.begin() + index);
    for (auto &row : resData) {
      row.erase(row.begin() + index);
    }
  }
  return IntermediateTable(resColNames, resData);
}

vector<string> concatColNames(const vector<string> &vector1,
                              const vector<string> &vector2) {
  vector<string> newVector;
  newVector.reserve(vector1.size() + vector2.size());
  std::copy(vector1.begin(), vector1.end(), std::back_inserter(newVector));
  std::copy(vector2.begin(), vector2.end(), std::back_inserter(newVector));
  return newVector;
}

vector<unique_ptr<SynonymRes>> concatRow(
    const vector<unique_ptr<SynonymRes>> &row1,
    const vector<unique_ptr<SynonymRes>> &row2) {
  vector<unique_ptr<SynonymRes>> rowCopy = {};
  for (const unique_ptr<SynonymRes> &val : row1) {
    rowCopy.emplace_back(val->clone());
  }
  for (const unique_ptr<SynonymRes> &val : row2) {
    rowCopy.emplace_back(val->clone());
  }
  return rowCopy;
}
