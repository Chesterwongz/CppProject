#include "IntermediateTableUtils.h"

#include <stdexcept>

#include "IntermediateTableFactory.h"
#include "common/utils/CollectionUtils.h"
#include "qps/exceptions/QPSIntermediateTableException.h"

vector<string> getSharedColNames(IntermediateTable table1,
                                 IntermediateTable table2) {
  vector<string> tableNames1 = table1.getColNames();
  vector<string> tableNames2 = table2.getColNames();
  return CollectionUtils::intersectVectors(tableNames1, tableNames2);
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
    throw QPSIntermediateTableException(
        QPS_UNSUPPORTED_CROSS_PRODUCT_EXCEPTION);
  }
  vector<string> resColumns =
      concatColNames(table1.getColNames(), table2.getColNames());
  TableDataType resData = {};
  for (const TableRowType &row1 : table1.getTableData()) {
    for (const TableRowType &row2 : table2.getTableData()) {
      resData.push_back(concatRow(row1, row2));
    }
  }
  return IntermediateTableFactory::buildIntermediateTable(resColumns,
                                                          std::move(resData));
}

IntermediateTable getInnerJoin(
    const pair<vector<int>, vector<int>> &sharedColumnIndexes,
    IntermediateTable table1, IntermediateTable table2) {
  vector<string> resColNames =
      concatColNames(table1.getColNames(), table2.getColNames());
  TableDataType resData = {};
  vector<int> table1SharedColIndexes = sharedColumnIndexes.first;
  vector<int> table2SharedColIndexes = sharedColumnIndexes.second;
  for (auto &table1Row : table1.getTableData()) {
    for (auto &table2Row : table2.getTableData()) {
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
        resData.emplace_back(std::move(concatRow(table1Row, table2Row)));
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
  return IntermediateTableFactory::buildIntermediateTable(resColNames,
                                                          std::move(resData));
}

vector<string> concatColNames(const vector<string> &vector1,
                              const vector<string> &vector2) {
  vector<string> newVector;
  newVector.reserve(vector1.size() + vector2.size());
  std::move(vector1.begin(), vector1.end(), std::back_inserter(newVector));
  std::move(vector2.begin(), vector2.end(), std::back_inserter(newVector));
  return newVector;
}

TableRowType concatRow(const TableRowType &row1, const TableRowType &row2) {
  TableRowType rowCopy = {};
  rowCopy.reserve(row1.size() + row2.size());
  // cannot move since the same row may have to be copied
  // multiple times for cross join
  for (const SynonymRes &val : row1) {
    rowCopy.emplace_back(val.clone());
  }
  for (const SynonymRes &val : row2) {
    rowCopy.emplace_back(val.clone());
  }
  return rowCopy;
}
