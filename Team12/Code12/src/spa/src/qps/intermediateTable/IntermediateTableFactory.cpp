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
  vector<vector<unique_ptr<SynonymRes>>> dataWithoutWildcardColumns = {};
  for (auto &dataPair : data) {
    vector<unique_ptr<SynonymRes>> row = {};
    if (!isFirstColWildcard) {
      row.emplace_back(std::make_unique<SynonymRes>(dataPair.first));
    }
    if (!isSecondColWildcard) {
      row.emplace_back(std::make_unique<SynonymRes>(dataPair.second));
    }
    dataWithoutWildcardColumns.emplace_back(std::move(row));
  }
  return IntermediateTable(columnNamesWithoutWildcard,
                           std::move(dataWithoutWildcardColumns));
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
  vector<vector<unique_ptr<SynonymRes>>> dataWithoutWildcardColumns = {};
  dataWithoutWildcardColumns.reserve(data.size());
  // add empty vector for each row
  for ([[maybe_unused]] const vector<string> &row : data) {
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
      unique_ptr<SynonymRes> synonymRes =
          std::make_unique<SynonymRes>(data.at(rowIndex).at(colIndex));
      dataWithoutWildcardColumns.at(rowIndex).emplace_back(
          std::move(synonymRes));
    }
  }
  return IntermediateTable(columnNamesWithoutWildcard,
                           std::move(dataWithoutWildcardColumns));
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
  vector<vector<unique_ptr<SynonymRes>>> dataColumn = {};
  dataColumn.reserve(data.size());
  for (const string &rowData : data) {
    vector<unique_ptr<SynonymRes>> row = {};
    row.push_back(std::make_unique<SynonymRes>(rowData));
    dataColumn.push_back(std::move(row));
  }
  return IntermediateTable(columnNames, std::move(dataColumn));
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
    const vector<string> &colNames,
    vector<vector<unique_ptr<SynonymRes>>> data) {
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
  vector<vector<unique_ptr<SynonymRes>>> dataWithoutWildcardColumns = {};
  dataWithoutWildcardColumns.reserve(data.size());
  // add empty vector for each row
  for ([[maybe_unused]] const vector<unique_ptr<SynonymRes>> &row : data) {
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
      dataWithoutWildcardColumns.at(rowIndex).push_back(
          std::move(data.at(rowIndex).at(colIndex)));
    }
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
