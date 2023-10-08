#include "IntermediateTableFactory.h"

#include "qps/common/Keywords.h"

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
    columnNamesWithoutWildcard.push_back(firstColName);
  }
  if (!isSecondColWildcard) {
    columnNamesWithoutWildcard.push_back(secondColName);
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
    dataWithoutWildcardColumns.push_back(row);
  }
  return IntermediateTable(columnNamesWithoutWildcard,
                           dataWithoutWildcardColumns);
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const vector<string> &colNames, const vector<vector<string>> &data) {
  // if data is empty, return empty table
  // even if columns are wildcard
  if (data.empty()) {
    return IntermediateTable::makeEmptyTable();
  }

  bool isAllWildcardColumns = std::count(colNames.begin(), colNames.end(),
                                         WILDCARD_KEYWORD) == colNames.size();
  if (isAllWildcardColumns) {
    return IntermediateTable::makeWildcardTable();
  }

  vector<string> columnNamesWithoutWildcard = {};
  vector<vector<SynonymRes>> dataWithoutWildcardColumns = {};
  dataWithoutWildcardColumns.reserve(data.size());
  // add empty vector for each row
  for ([[maybe_unused]] auto &row : data) {
    dataWithoutWildcardColumns.emplace_back();
  }
  for (int colIndex = 0; colIndex < colNames.size(); colIndex++) {
    const string &colName = colNames.at(colIndex);
    if (colName == WILDCARD_KEYWORD) {
      // ignore wildcard columns
      continue;
    }
    columnNamesWithoutWildcard.push_back(colName);
    for (int rowIndex = 0; rowIndex < data.size(); rowIndex++) {
      string elementToAdd = data.at(rowIndex).at(colIndex);
      dataWithoutWildcardColumns.at(rowIndex).emplace_back(elementToAdd);
    }
  }
  return IntermediateTable(columnNamesWithoutWildcard,
                           dataWithoutWildcardColumns);
}

IntermediateTable IntermediateTableFactory::buildSingleColTable(
    const string &colName, const vector<string> &data) {
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
    row.emplace_back(rowData);
    dataColumn.emplace_back(row);
  }
  return IntermediateTable(columnNames, dataColumn);
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const string &firstColName, const set<string> &data) {
  vector<string> dataAsVector(data.begin(), data.end());
  return buildSingleColTable(firstColName, dataAsVector);
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const string &colName, const string &value) {
  vector<string> dataCol = {value};
  return IntermediateTableFactory::buildSingleColTable(colName, dataCol);
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const vector<string> &colNames, const vector<vector<SynonymRes>> &data) {
  // if data is empty, return empty table
  // even if columns are wildcard
  if (data.empty()) {
    return IntermediateTable::makeEmptyTable();
  }

  bool isAllWildcardColumns = std::count(colNames.begin(), colNames.end(),
                                         WILDCARD_KEYWORD) == colNames.size();
  if (isAllWildcardColumns) {
    return IntermediateTable::makeWildcardTable();
  }

  vector<string> columnNamesWithoutWildcard = {};
  vector<vector<SynonymRes>> dataWithoutWildcardColumns = {};
  dataWithoutWildcardColumns.reserve(data.size());
  // add empty vector for each row
  for ([[maybe_unused]] auto &row : data) {
    dataWithoutWildcardColumns.emplace_back();
  }
  for (int colIndex = 0; colIndex < colNames.size(); colIndex++) {
    const string &colName = colNames.at(colIndex);
    if (colName == WILDCARD_KEYWORD) {
      // ignore wildcard columns
      continue;
    }
    columnNamesWithoutWildcard.push_back(colName);
    for (int rowIndex = 0; rowIndex < data.size(); rowIndex++) {
      SynonymRes elementToAdd = data.at(rowIndex).at(colIndex);
      dataWithoutWildcardColumns.at(rowIndex).push_back(elementToAdd);
    }
  }
  return IntermediateTable(columnNamesWithoutWildcard,
                           dataWithoutWildcardColumns);
}

IntermediateTable IntermediateTableFactory::buildEmptyIntermediateTable() {
  return IntermediateTable::makeEmptyTable();
}

IntermediateTable IntermediateTableFactory::buildWildcardIntermediateTable() {
  return IntermediateTable::makeWildcardTable();
}
