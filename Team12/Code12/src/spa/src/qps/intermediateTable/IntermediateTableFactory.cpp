#include "IntermediateTableFactory.h"

#include "qps/common/Keywords.h"

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const string &firstColName, const string &secondColName,
    vector<pair<std::string, std::string>> data) {
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
  vector<vector<SynonymRes>> dataWithoutWildcardColumns = {};
  for (auto &dataPair : data) {
    vector<SynonymRes> row = {};
    if (!isFirstColWildcard) {
      row.emplace_back(dataPair.first);
    }
    if (!isSecondColWildcard) {
      row.emplace_back(dataPair.second);
    }
    dataWithoutWildcardColumns.emplace_back(std::move(row));
  }
  return IntermediateTable(columnNamesWithoutWildcard,
                           std::move(dataWithoutWildcardColumns));
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const vector<string> &colNames, vector<vector<string>> data) {
  return IntermediateTableFactory::tableBuilderHelper(colNames, std::move(data));
}

IntermediateTable IntermediateTableFactory::buildSingleColTable(
    const string &colName, vector<string> data) {
  // if data is empty, return empty table
  // even if columns are wildcard
  if (data.empty()) {
    return IntermediateTable::makeEmptyTable();
  }

  if (colName == WILDCARD_KEYWORD) {
    return IntermediateTable::makeWildcardTable();
  }

  vector<string> columnNames = {colName};
  vector<vector<SynonymRes>> dataColumn = {};
  dataColumn.reserve(data.size());
  for (const string &rowData : data) {
    vector<SynonymRes> row = {};
    row.emplace_back(std::move(rowData));
    dataColumn.emplace_back(std::move(row));
  }
  return IntermediateTable(columnNames, std::move(dataColumn));
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const string &firstColName, set<string> data) {
  vector<string> dataAsVector(data.begin(), data.end());
  return buildSingleColTable(firstColName, std::move(dataAsVector));
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const string &colName, string value) {
  vector<string> dataCol = {std::move(value)};
  return IntermediateTableFactory::buildSingleColTable(colName,
                                                       std::move(dataCol));
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const vector<string> &colNames, vector<vector<SynonymRes>> data) {
  return IntermediateTableFactory::tableBuilderHelper(colNames,
                                                      std::move(data));
}

IntermediateTable IntermediateTableFactory::buildEmptyIntermediateTable() {
  return IntermediateTable::makeEmptyTable();
}

IntermediateTable IntermediateTableFactory::buildWildcardIntermediateTable() {
  return IntermediateTable::makeWildcardTable();
}
