#include "IntermediateTableUtils.h"

#include <cassert>
#include <stdexcept>

#include "IntermediateTableFactory.h"
#include "common/utils/CollectionUtils.h"

vector<string> IntermediateTableUtils::getSharedColNames(
    const IntermediateTable& table1, const IntermediateTable& table2) {
  const vector<string>& tableNames1 = table1.getColNames();
  const vector<string>& tableNames2 = table2.getColNames();
  return CollectionUtils::intersectVectors(tableNames1, tableNames2);
}

pair<vector<int>, vector<int>> IntermediateTableUtils::getSharedColIndexes(
    const IntermediateTable& table1, const IntermediateTable& table2) {
  vector<string> sharedColNames =
      IntermediateTableUtils::getSharedColNames(table1, table2);

  vector<int> table1Indexes, table2Indexes;
  table1Indexes.reserve(sharedColNames.size());
  table2Indexes.reserve(sharedColNames.size());
  std::transform(sharedColNames.begin(), sharedColNames.end(),
                 std::back_inserter(table1Indexes),
                 [&table1](const string& colName) -> int {
                   return table1.getColIndex(colName);
                 });

  std::transform(sharedColNames.begin(), sharedColNames.end(),
                 std::back_inserter(table2Indexes),
                 [&table2](const string& colName) -> int {
                   return table2.getColIndex(colName);
                 });

  return {table1Indexes, table2Indexes};
}

IntermediateTable IntermediateTableUtils::getCrossProduct(
    const IntermediateTable& table1, const IntermediateTable& table2) {
  assert(IntermediateTableUtils::getSharedColNames(table1, table2).empty());

  vector<string> resColumns = IntermediateTableUtils::getJoinColNames(
      table1.getColNames(), table2.getColNames(), {});

  TableDataType resData;
  resData.reserve(table1.getRowCount() * table2.getRowCount());
  for (const TableRowType& row1 : table1.getTableData()) {
    for (const TableRowType& row2 : table2.getTableData()) {
      resData.emplace_back(concatRow(row1, row2));
    }
  }

  return IntermediateTableFactory::buildIntermediateTable(resColumns,
                                                          std::move(resData));
}

IntermediateTable IntermediateTableUtils::getInnerJoin(
    const pair<vector<int>, vector<int>>& sharedColumnIndexes,
    const IntermediateTable& t1, const IntermediateTable& t2) {
  TableDataType resData;
  auto& [t1SharedColIndexes, t2SharedColIndexes] = sharedColumnIndexes;
  // Use a hashmap to optimize lookup
  // Key: concatenated values of shared columns,
  // Value: list of rows with that key
  unordered_map<string, vector<TableRowType>> t2Mapping;
  for (const TableRowType& t2Row : t2.getTableData()) {
    string key;
    for (const int idx : t2SharedColIndexes) {
      // use delimiter to differentiate values
      key += t2Row.at(idx).toString() + "|";
    }
    t2Mapping[key].emplace_back(t2Row);
  }

  unordered_set<size_t> t2SharedColIndexesSet = {t2SharedColIndexes.begin(),
                                                 t2SharedColIndexes.end()};
  for (const TableRowType& t1Row : t1.getTableData()) {
    string key;
    for (const int idx : t1SharedColIndexes) {
      key += t1Row.at(idx).toString() + "|";
    }
    if (t2Mapping.find(key) == t2Mapping.end()) continue;

    for (const TableRowType& t2Row : t2Mapping[key]) {
      vector<SynonymRes> resRow(t1Row.begin(), t1Row.end());

      for (size_t i = 0; i < t2Row.size(); i++) {
        if (t2SharedColIndexesSet.count(i) == 0) {
          resRow.push_back(t2Row.at(i));
        }
      }

      resData.emplace_back(std::move(resRow));
    }
  }

  vector<string> resColNames = IntermediateTableUtils::getJoinColNames(
      t1.getColNames(), t2.getColNames(), t2SharedColIndexesSet);
  return IntermediateTableFactory::buildIntermediateTable(resColNames,
                                                          std::move(resData));
}

IntermediateTable IntermediateTableUtils::getInnerJoinOn(
    const IntermediateTable& t1, const IntermediateTable& t2,
    const pair<string, AttrRef>& joinColT1,
    const pair<string, AttrRef>& joinColT2) {
  vector<string> sharedCols = getSharedColNames(t1, t2);
  assert(sharedCols.empty() ||
         (sharedCols.size() == 1 && sharedCols.at(0) == joinColT1.first &&
          sharedCols.at(0) == joinColT2.first));

  TableDataType resData;
  auto& [t1ColName, t1AttrRef] = joinColT1;
  auto& [t2ColName, t2AttrRef] = joinColT2;

  if (!t1.isColExists(t1ColName) || !t2.isColExists(t2ColName)) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  size_t t1JoinColIndex = t1.getColIndex(t1ColName);
  size_t t2JoinColIndex = t2.getColIndex(t2ColName);
  if (t1JoinColIndex == IntermediateTableUtils::INVALID_COL_INDEX ||
      t2JoinColIndex == IntermediateTableUtils::INVALID_COL_INDEX) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  // Use a hashmap to optimize lookup
  unordered_map<string, vector<TableRowType>> t2Mapping;
  for (const TableRowType& t2Row : t2.getTableData()) {
    string key = t2Row.at(t2JoinColIndex).getAttribute(t2AttrRef);
    t2Mapping[key].push_back(t2Row);
  }

  for (const TableRowType& t1Row : t1.getTableData()) {
    string key = t1Row.at(t1JoinColIndex).getAttribute(t1AttrRef);
    if (t2Mapping.find(key) == t2Mapping.end()) continue;
    for (const TableRowType& t2Row : t2Mapping[key]) {
      vector<SynonymRes> resRow(t1Row.begin(), t1Row.end());

      for (size_t i = 0; i < t2Row.size(); ++i) {
        if (t1ColName != t2ColName || i != t2JoinColIndex) {
          resRow.push_back(t2Row.at(i));
        }
      }

      resData.emplace_back(std::move(resRow));
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
    const vector<string>& t1Names, const vector<string>& t2Names,
    const unordered_set<size_t>& t2SharedColIndexes) {
  vector<string> resColNames;
  resColNames.reserve(t1Names.size() + t2Names.size() -
                      t2SharedColIndexes.size());
  resColNames.insert(resColNames.end(), t1Names.begin(), t1Names.end());
  for (size_t i = 0; i < t2Names.size(); i++) {
    if (t2SharedColIndexes.count(i) == 0) {
      resColNames.push_back(t2Names[i]);
    }
  }
  return resColNames;
}

TableRowType IntermediateTableUtils::concatRow(const TableRowType& row1,
                                               const TableRowType& row2) {
  // cannot move since the same row may have to be copied
  // multiple times for cross join
  TableRowType rowCopy {};
  rowCopy.reserve(row1.size() + row2.size());  // preallocate memory
  rowCopy.insert(rowCopy.end(), row1.begin(), row1.end());
  rowCopy.insert(rowCopy.end(), row2.begin(), row2.end());
  return rowCopy;
}
