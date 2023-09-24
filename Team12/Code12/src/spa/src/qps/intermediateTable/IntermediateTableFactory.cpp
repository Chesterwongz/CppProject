#include "IntermediateTableFactory.h"
#include "qps/common/Keywords.h"

 IntermediateTable IntermediateTableFactory::buildIntermediateTable(
        const string &firstColName,
        const string &secondColName,
        const vector<pair<std::string, std::string>> &data) {
    // if data is empty, return empty table
    // even if columns are wildcard
    if (data.empty()) {
        return IntermediateTable::makeEmptyTable();;
    }

    bool isFirstColWildcard = firstColName == WILDCARD_KEYWORD;
    bool isSecondColWildcard = secondColName == WILDCARD_KEYWORD;
    if (isFirstColWildcard && isSecondColWildcard) {
        return IntermediateTable::makeWildcardTable();
    }
    if (!isFirstColWildcard && !isSecondColWildcard) {
        return IntermediateTable(firstColName,
                                 secondColName,
                                 data);
    }

    vector<string> columnNamesWithoutWildcard = {};
    if (!isFirstColWildcard) {
        columnNamesWithoutWildcard.push_back(firstColName);
    }
    if (!isSecondColWildcard) {
        columnNamesWithoutWildcard.push_back(secondColName);
    }
    vector<vector<string>> dataWithoutWildcardColumns = {};
    for (auto &dataPair : data) {
        vector<string> row = {};
        if (!isFirstColWildcard) {
            row.push_back(dataPair.first);
        }
        if (!isSecondColWildcard) {
            row.push_back(dataPair.second);
        }
        dataWithoutWildcardColumns.push_back(row);
    }
    return IntermediateTable(columnNamesWithoutWildcard,
                             dataWithoutWildcardColumns);
}

IntermediateTable IntermediateTableFactory::buildIntermediateTable(
        const vector<string> &colNames,
        const vector<vector<string>> &data) {
    // if data is empty, return empty table
    // even if columns are wildcard
    if (data.empty()) {
        return IntermediateTable::makeEmptyTable();
    }

    bool isAllWildcardColumns = std::count(colNames.begin(),
                                           colNames.end(),
                                           WILDCARD_KEYWORD)
                                                   == colNames.size();
    if (isAllWildcardColumns) {
        return IntermediateTable::makeWildcardTable();
    }

    vector<string> columnNamesWithoutWildcard = {};
    vector<vector<string>> dataWithoutWildcardColumns = {};
    dataWithoutWildcardColumns.reserve(data.size());
    for ([[maybe_unused]] auto &row : data) { dataWithoutWildcardColumns.emplace_back(); }
    for (int colIndex = 0; colIndex < colNames.size(); colIndex++) {
        const string& colName = colNames.at(colIndex);
        if (colName == WILDCARD_KEYWORD) {
            // ignore wildcard columns
            continue;
        }
        columnNamesWithoutWildcard.push_back(colName);
        for (int rowIndex = 0; rowIndex < data.size(); rowIndex++) {
            string elementToAdd = data.at(rowIndex).at(colIndex);
            dataWithoutWildcardColumns.at(rowIndex).push_back(elementToAdd);
        }

    }
    return IntermediateTable(columnNamesWithoutWildcard,
                             dataWithoutWildcardColumns);
}

IntermediateTable IntermediateTableFactory::buildSingleColTable(
        const string &colName,
        const vector<string> &data) {
    // if data is empty, return empty table
    // even if columns are wildcard
    if (data.empty()) {
        return IntermediateTable::makeEmptyTable();
    }

    if (colName == WILDCARD_KEYWORD) {
        return IntermediateTable::makeWildcardTable();
    }

    vector<string> columnNames = { colName };
    vector<vector<string>> dataColumn = {};
    dataColumn.reserve(data.size());
    for (int rowIndex = 0; rowIndex < data.size(); rowIndex++) {
        vector<string> elementToAdd = {data.at(rowIndex)};
        dataColumn.push_back(elementToAdd);
    }
    return IntermediateTable(columnNames,
                             dataColumn);
}

IntermediateTable IntermediateTableFactory::buildEmptyIntermediateTable() {
    return IntermediateTable::makeEmptyTable();;
}

IntermediateTable IntermediateTableFactory::buildWildcardIntermediateTable() {
    return IntermediateTable::makeWildcardTable();
};
