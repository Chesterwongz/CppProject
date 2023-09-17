#include <stdexcept>
#include "IntermediateTable.h"
#include "IntermediateTableUtils.h"

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
}


int IntermediateTable::createNewCol(const string &newColName) {
    this->colNameToIndexMap[newColName] = this->currentColCount;
    this->colNames.push_back(newColName);
    return this->currentColCount++;
}

vector<vector<string>> IntermediateTable::getData() {
    return this->tableData;
}

vector<string> IntermediateTable::getSingleCol(const string &colName) {
    if (!isColExists(colName)) {
        throw std::runtime_error("Non-existent column name");
    }
    int colIndex = this->colNameToIndexMap.at(colName);
    vector<string> res = {};
    res.reserve(this->tableData.size());
    for (auto &row : this->tableData) {
        res.push_back(row.at(colIndex));
    }
    return res;
}

vector<vector<string>> IntermediateTable::getCol(
        const vector<string> &colNameVector) {
    vector<vector<string>> res = {};
    res.reserve(this->tableData.size());
    for (int rowIndex = 0; rowIndex < tableData.size(); rowIndex++) {
        vector<string> row = {};
        row.reserve(colNameVector.size());
        for (const string &colName : colNameVector) {
            if (this->colNameToIndexMap.find(colName) == this->colNameToIndexMap.end()) {
                throw std::runtime_error("Non-existent column name");
            }
            int colIndex = this->colNameToIndexMap.at((colName));
            row.push_back(this->tableData.at(rowIndex).at(colIndex));
        }
        res.push_back(row);
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

IntermediateTable IntermediateTable::join(const IntermediateTable& intermediateTable) {
    pair<vector<int>, vector<int>> sharedColumnIndexes =
            getSharedColIndexes(*this, intermediateTable);
    bool noSharedColumns =
            sharedColumnIndexes.first.empty() && sharedColumnIndexes.second.empty();
    if (noSharedColumns) {
        return getCrossProduct(*this, intermediateTable);
    }
    return getInnerJoin(sharedColumnIndexes, *this, intermediateTable);
}
