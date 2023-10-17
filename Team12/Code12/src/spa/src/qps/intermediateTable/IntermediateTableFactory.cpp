#include "IntermediateTableFactory.h"

#include "qps/common/Keywords.h"
#include "qps/intermediateTable/synonymRes/SynonymResFactory.h"

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
    const vector<string> &colNames, vector<vector<string>> data) {
  return IntermediateTableFactory::tableBuilderHelper(colNames,
                                                      std::move(data));
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const string &firstColName, set<string> data) {
  vector<string> dataAsVector(data.begin(), data.end());
  return buildSingleColTable(firstColName, dataAsVector);
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const string &colName, string value) {
  vector<string> dataCol = {std::move(value)};
  return IntermediateTableFactory::buildSingleColTable(colName, dataCol);
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
    const vector<string> &colNames, TableDataType data) {
  return IntermediateTableFactory::tableBuilderHelper(colNames,
                                                      std::move(data));
}

IntermediateTable IntermediateTableFactory::buildEmptyIntermediateTable() {
  return IntermediateTable::makeEmptyTable();
}

IntermediateTable IntermediateTableFactory::buildWildcardIntermediateTable() {
  return IntermediateTable::makeWildcardTable();
}
