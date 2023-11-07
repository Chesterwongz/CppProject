#include "IntermediateTableFactory.h"

#include <cassert>

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const string &firstColName, const string &secondColName,
    const vector<pair<std::string, std::string>> &data) {
  // if data is empty, return empty table
  // even if columns are wildcard
  if (data.empty()) {
    return IntermediateTable::makeEmptyTable();
  }

  bool isFirstColWildcard = firstColName == WILDCARD_KEYWORD;
  bool isSecondColWildcard = secondColName == WILDCARD_KEYWORD;
  if (isFirstColWildcard && isSecondColWildcard) {
    return IntermediateTable::makeWildcardTable();
  }

  vector<string> columnNamesWithoutWildcard = {};
  if (!isFirstColWildcard) {
    columnNamesWithoutWildcard.emplace_back(firstColName);
  }
  if (!isSecondColWildcard) {
    columnNamesWithoutWildcard.emplace_back(secondColName);
  }
  TableDataType dataWithoutWildcardColumns = {};
  for (auto &dataPair : data) {
    TableRowType row = {};
    if (!isFirstColWildcard) {
      row.emplace_back(SynonymResFactory::buildDefaultSynonym(dataPair.first));
    }
    if (!isSecondColWildcard) {
      row.emplace_back(SynonymResFactory::buildDefaultSynonym(dataPair.second));
    }
    dataWithoutWildcardColumns.emplace_back(std::move(row));
  }
  return IntermediateTable(columnNamesWithoutWildcard,
                           std::move(dataWithoutWildcardColumns));
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const string &colName, std::reference_wrapper<SynonymRes> value) {
  vector<std::reference_wrapper<SynonymRes>> dataCol = {value};
  return IntermediateTableFactory::buildSingleColTable(colName, dataCol);
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const vector<string> &colNames, TableDataType data) {
  vector<size_t> nonWildcardColIdx {};
  vector<string> columnNamesWithoutWildcard {};
  nonWildcardColIdx.reserve(colNames.size());
  columnNamesWithoutWildcard.reserve(colNames.size());
  for (size_t i = 0; i < colNames.size(); i++) {
    if (colNames.at(i) != WILDCARD_KEYWORD) {
      nonWildcardColIdx.emplace_back(i);
      columnNamesWithoutWildcard.emplace_back(colNames.at(i));
    }
  }
  if (nonWildcardColIdx.size() == colNames.size()) {
    // no wildcard cols
    return buildWithoutWildcardFilter(colNames, std::move(data));
  }
  assert(data.empty() || colNames.size() == data.at(0).size());

  // if data is empty, return empty table even if columns are wildcard
  if (data.empty()) {
    return IntermediateTable::makeEmptyTable();
  }

  if (nonWildcardColIdx.empty()) {
    // all wildcard cols
    return IntermediateTable::makeWildcardTable();
  }

  TableDataType dataWithoutWildcardColumns = {};
  dataWithoutWildcardColumns.reserve(data.size());

  for (int rowIndex = 0; rowIndex < data.size(); rowIndex++) {
    TableRowType row {};
    row.reserve(nonWildcardColIdx.size());
    for (const size_t &colIndex : nonWildcardColIdx) {
      row.emplace_back(std::move(data.at(rowIndex).at(colIndex)));
    }
    dataWithoutWildcardColumns.emplace_back(std::move(row));
  }
  return IntermediateTable(columnNamesWithoutWildcard,
                           std::move(dataWithoutWildcardColumns));
}

IntermediateTable IntermediateTableFactory::buildEmptyIntermediateTable() {
  return IntermediateTable::makeEmptyTable();
}

IntermediateTable IntermediateTableFactory::buildWildcardIntermediateTable() {
  return IntermediateTable::makeWildcardTable();
}

IntermediateTable IntermediateTableFactory::buildWithoutWildcardFilter(
    const vector<string> &colNames, TableDataType data) {
  assert(std::find(colNames.begin(), colNames.end(), WILDCARD_KEYWORD) ==
         colNames.end());
  if (data.empty()) {
    return IntermediateTable::makeEmptyTable();
  }

  return IntermediateTable(colNames, std::move(data));
}
