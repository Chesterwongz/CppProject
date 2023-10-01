#include <stdexcept>
#include <iostream>
#include "IntermediateTable.h"
#include "IntermediateTableUtils.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

IntermediateTable::IntermediateTable(bool isTableWildcard):
    isWildcard(isTableWildcard),
    isEmpty(true) {}

IntermediateTable::IntermediateTable(
        const string &firstColName,
        const string &secondColName,
        const vector<pair<string, string>>& data
        ) {
    IntermediateTable::createNewCol(firstColName);
    IntermediateTable::createNewCol(secondColName);
    for (auto &dataPair : data) {
        vector<string> row = {};
        row.push_back(dataPair.first);
        row.push_back(dataPair.second);
        this->tableData.push_back(row);
    }
    this->isEmpty = false;
}

IntermediateTable::IntermediateTable(
        const vector<string> &colNames,
        const vector<vector<string>> &data) {
    for (auto &colName : colNames) {
        IntermediateTable::createNewCol(colName);
    }
    for (auto &dataRow : data) {
        this->tableData.push_back(dataRow);
    }
    this->isEmpty = false;
}

IntermediateTable IntermediateTable::makeWildcardTable() {
    bool isTableWildcard = true;
    // note: wildcard tables are empty
    return IntermediateTable(isTableWildcard);
}

IntermediateTable IntermediateTable::makeEmptyTable() {
    bool isTableWildcard = false;
    return IntermediateTable(isTableWildcard);
}

int IntermediateTable::createNewCol(const string &newColName) {
    this->isEmpty = false;
    this->colNameToIndexMap[newColName] = this->currentColCount;
    this->colNames.push_back(newColName);
    return this->currentColCount++;
}

vector<vector<string>> IntermediateTable::getData() {
    return this->tableData;
}

set<string> IntermediateTable::getColumns(
        const vector<string> &colNameVector) {
    if (colNameVector.empty()) {
        return {};
    }

    for (const string &colName : colNameVector) {
        // return empty if any column requested does not exist
        if (!this->isColExists(colName)) {
            return {};
        }
    }

    set<string> res = {};
    for (int rowIndex = 0; rowIndex < this->getRowCount(); rowIndex++) {
        string row = "";
        for (const string &colName : colNameVector) {
            int colIndex = this->colNameToIndexMap.at(colName);
            row += (row.empty() ? "" : " ") + this->tableData.at(rowIndex).at(colIndex);
        }
        res.insert(row);
    }
    return res;
}

vector<string> IntermediateTable::getColNames() {
    return this->colNames;
}

int IntermediateTable::getColIndex(const string &colName) {
    if (!isColExists(colName)) {
        return -1;
    }
    return this->colNameToIndexMap.at(colName);
}

bool IntermediateTable::isColExists(const std::string &colName) {
    return this->colNameToIndexMap.find(colName) != this->colNameToIndexMap.end();
}

int IntermediateTable::getRowCount() {
    return this->tableData.size();
}

bool IntermediateTable::isTableWildcard() const {
    return this->isWildcard;
}

bool IntermediateTable::isTableEmpty() const {
    return this->isEmpty;
}

bool IntermediateTable::isTableEmptyAndNotWildcard() const {
    return !this->isTableWildcard() && this->isTableEmpty();
}

IntermediateTable IntermediateTable::join(const IntermediateTable& intermediateTable) {
    if (this->isTableWildcard() && intermediateTable.isTableWildcard()) {
        // WILDCARD x WILDCARD = WILDCARD
        return intermediateTable;
    }
    if (this->isTableEmptyAndNotWildcard() || intermediateTable.isTableEmptyAndNotWildcard()) {
        // (ANY x EMPTY || EMPTY x ANY) = EMPTY
        return IntermediateTable::makeEmptyTable();
    }
    if (this->isTableWildcard() && !intermediateTable.isTableWildcard()) {
        // WILDCARD X TABLE_2 = TABLE_2
        return intermediateTable;
    }
    if (!this->isTableWildcard() && intermediateTable.isTableWildcard()) {
        // TABLE_1 x WILDCARD = TABLE_1
        return *this;
    }

    pair<vector<int>, vector<int>> sharedColumnIndexes =
            getSharedColIndexes(*this, intermediateTable);
    bool noSharedColumns =
            sharedColumnIndexes.first.empty() && sharedColumnIndexes.second.empty();

    // Cross if no shared columns, inner join if shared columns exists
    return noSharedColumns ?
        getCrossProduct(*this, intermediateTable)
        : getInnerJoin(sharedColumnIndexes, *this, intermediateTable);
}

void IntermediateTable::printTable() {
    std::cout << "table: " << std::endl;
    if (this->isWildcard || this->isEmpty) {
        std::cout << (isWildcard ? "WILDCARD" : "EMPTY") << std::endl;
        return;
    }
    string colNamesToPrint;
    for (auto &colName : this->getColNames()) {
        colNamesToPrint += colName + " | ";
    }
    std::cout << colNamesToPrint << std::endl;

    for (auto &row : this->getData()) {
        string rowDataToPrint;
        for (auto &col : row) {
            rowDataToPrint += col + " | ";
        }
        std::cout << rowDataToPrint << std::endl;
    }
}
