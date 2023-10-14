#include "IntermediateTableUtils.h"

#include <stdexcept>

#include "common/utils/VectorUtils.h"

vector<string> getSharedColNames(IntermediateTable table1,
                                 IntermediateTable table2) {
  vector<string> tableNames1 = table1.getColNames();
  vector<string> tableNames2 = table2.getColNames();
  return VectorUtils::intersectVectors(tableNames1, tableNames2);
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
      VectorUtils::concatVectors<string>(table1.getColNames(), table2.getColNames());
  vector<vector<string>> resData = {};
  for (auto &row1 : table1.getData()) {
    for (auto &row2 : table2.getData()) {
      resData.push_back(VectorUtils::concatVectors<string>(row1, row2));
    }
  }
  return IntermediateTable(resColumns, resData);
}

IntermediateTable getInnerJoin(
    const pair<vector<int>, vector<int>> &sharedColumnIndexes,
    IntermediateTable table1, IntermediateTable table2) {
  vector<string> resColNames =
      VectorUtils::concatVectors(table1.getColNames(), table2.getColNames());
  vector<vector<string>> resData = {};
  vector<int> table1SharedColIndexes = sharedColumnIndexes.first;
  vector<int> table2SharedColIndexes = sharedColumnIndexes.second;
  for (auto &table1Row : table1.getData()) {
    for (auto &table2Row : table2.getData()) {
      bool isJoin = true;
      for (int i = 0; i < table1SharedColIndexes.size(); i++) {
        // check that for this particular row,
        // all elements in shared cols of table 1
        // matches with all elements in shared cols of table 2
        int table1ColIndex = table1SharedColIndexes.at(i);
        int table2ColIndex = table2SharedColIndexes.at(i);
        if (table1Row.at(table1ColIndex) != table2Row.at(table2ColIndex)) {
          isJoin = false;
          break;
        }
      }
      if (isJoin) {
        vector<string> resRow;
        resData.push_back(VectorUtils::concatVectors(table1Row, table2Row));
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
