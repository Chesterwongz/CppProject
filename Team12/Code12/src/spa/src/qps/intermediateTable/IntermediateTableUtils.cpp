#include "IntermediateTableUtils.h"

#include <cassert>
#include <stdexcept>

#include "IntermediateTableFactory.h"
#include "common/utils/CollectionUtils.h"

vector<string> IntermediateTableUtils::getSharedColNames(
    const IntermediateTable &table1, const IntermediateTable &table2) {
  vector<string> tableNames1 = table1.getColNames();
  vector<string> tableNames2 = table2.getColNames();
  return CollectionUtils::intersectVectors(tableNames1, tableNames2);
}

pair<vector<int>, vector<int>> IntermediateTableUtils::getSharedColIndexes(
    IntermediateTable table1, IntermediateTable table2) {
  vector<string> sharedColNames =
      IntermediateTableUtils::getSharedColNames(table1, table2);
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

IntermediateTable IntermediateTableUtils::getCrossProduct(
    const IntermediateTable &table1, const IntermediateTable &table2) {
  assert(IntermediateTableUtils::getSharedColNames(table1, table2).empty());
  vector<string> resColumns = IntermediateTableUtils::getJoinColNames(
      table1.getColNames(), table2.getColNames(), {});
  TableDataType resData = {};
  resData.reserve(table1.getRowCount() * table2.getRowCount());
  for (const TableRowType &row1 : table1.getTableData()) {
    for (const TableRowType &row2 : table2.getTableData()) {
      resData.emplace_back(IntermediateTableUtils::concatRow(row1, row2));
    }
  }
  return IntermediateTableFactory::buildIntermediateTable(resColumns,
                                                          std::move(resData));
}

IntermediateTable IntermediateTableUtils::getInnerJoin(
    const pair<vector<int>, vector<int>> &sharedColumnIndexes,
    const IntermediateTable &t1, const IntermediateTable &t2) {
  TableDataType resData {};
  auto &[t1SharedColIndexes, t2SharedColIndexes] = sharedColumnIndexes;
  // need this for o(1) search of t2 indexes
  unordered_set<size_t> t2SharedColIndexesSet(t2SharedColIndexes.begin(),
                                              t2SharedColIndexes.end());
  for (TableRowType &t1Row : t1.getTableData()) {
    for (TableRowType &t2Row : t2.getTableData()) {
      bool isJoin = true;
      for (int i = 0; i < t1SharedColIndexes.size(); i++) {
        // for each t1-t2 row combination, check that all elements in shared
        // cols of t1 matches with all elements in shared cols of t2
        int t1ColIndex = t1SharedColIndexes.at(i);
        int t2ColIndex = t2SharedColIndexes.at(i);
        if (t1Row.at(t1ColIndex) != t2Row.at(t2ColIndex)) {
          isJoin = false;
          break;
        }
      }
      if (isJoin) {
        vector<SynonymRes> resRow(t1Row.begin(), t1Row.end());
        for (size_t i = 0; i < t2Row.size(); i++) {
          if (t2SharedColIndexesSet.find(i) == t2SharedColIndexesSet.end()) {
            // only insert cols that aren't shared with t 1
            resRow.push_back(t2Row.at(i));
          }
        }
        resData.emplace_back(std::move(resRow));
      }
    }
  }
  vector<string> resColNames = IntermediateTableUtils::getJoinColNames(
      t1.getColNames(), t2.getColNames(), t2SharedColIndexesSet);
  return IntermediateTableFactory::buildIntermediateTable(resColNames,
                                                          std::move(resData));
}

IntermediateTable IntermediateTableUtils::getInnerJoinOn(
    const IntermediateTable &t1, const IntermediateTable &t2,
    const pair<string, AttrRef> &joinColT1,
    const pair<string, AttrRef> &joinColT2) {
  // either there are no shared columns, or we are joining on the
  // only shared column
  assert(getSharedColNames(t1, t2).empty() ||
         (getSharedColNames(t1, t2).size() == 1 &&
          getSharedColNames(t1, t2).at(0) == joinColT1.first &&
          getSharedColNames(t1, t2).at(0) == joinColT2.first));
  TableDataType resData = {};
  auto &[t1ColName, t1AttrRef] = joinColT1;
  auto &[t2ColName, t2AttrRef] = joinColT2;
  if (!t1.isColExists(t1ColName) || !t2.isColExists(t2ColName)) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  size_t t1JoinColIndex = t1.getColIndex(t1ColName);
  size_t t2JoinColIndex = t2.getColIndex(t2ColName);
  if (t1JoinColIndex == IntermediateTableUtils::INVALID_COL_INDEX ||
      t2JoinColIndex == IntermediateTableUtils::INVALID_COL_INDEX) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  for (TableRowType &t1Row : t1.getTableData()) {
    for (TableRowType &t2Row : t2.getTableData()) {
      bool isJoin = t1Row.at(t1JoinColIndex).getAttribute(t1AttrRef) ==
                    t2Row.at(t2JoinColIndex).getAttribute(t2AttrRef);
      if (isJoin) {
        vector<SynonymRes> resRow(t1Row.begin(), t1Row.end());
        for (size_t i = 0; i < t2Row.size(); i++) {
          if (t1ColName != t2ColName || i != t2JoinColIndex) {
            // skip repeated col in t2
            resRow.push_back(t2Row.at(i));
          }
        }
        resData.emplace_back(std::move(resRow));
      }
    }
  }

  vector<string> resColNames =
      t1ColName == t2ColName
          ? IntermediateTableUtils::getJoinColNames(
                t1.getColNames(), t2.getColNames(), {t2JoinColIndex})
          : IntermediateTableUtils::getJoinColNames(t1.getColNames(),
                                                    t2.getColNames(), {});

  return IntermediateTableFactory::buildIntermediateTable(resColNames,
                                                          std::move(resData));
}

vector<string> IntermediateTableUtils::getJoinColNames(
    const vector<string> &t1Names, const vector<string> &t2Names,
    unordered_set<size_t> t2SharedColIndexes) {
  vector<string> resColNames(t1Names.begin(), t1Names.end());
  for (size_t i = 0; i < t2Names.size(); i++) {
    if (t2SharedColIndexes.find(i) == t2SharedColIndexes.end()) {
      // only insert col names not joined on
      resColNames.emplace_back(t2Names.at(i));
    }
  }
  return resColNames;
}

TableRowType IntermediateTableUtils::concatRow(const TableRowType &row1,
                                               const TableRowType &row2) {
  // cannot move since the same row may have to be copied
  // multiple times for cross join
  TableRowType rowCopy{};
  rowCopy.reserve(row1.size() + row2.size());  // preallocate memory
  rowCopy.insert(rowCopy.end(), row1.begin(), row1.end());
  rowCopy.insert(rowCopy.end(), row2.begin(), row2.end());
  return rowCopy;
}
