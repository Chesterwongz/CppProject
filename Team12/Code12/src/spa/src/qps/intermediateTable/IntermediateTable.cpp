#include <stdexcept>
#include "IntermediateTable.h"

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
        table.push_back(row);
    }
}

IntermediateTable::IntermediateTable(
        const vector<string> &colNames,
        const vector<vector<string>> &data) {
    for (auto &colName : colNames) {
        IntermediateTable::createNewCol(colName);
    }
    for (auto &dataRow : data) {
        table.push_back(dataRow);
    }
}

vector<string> IntermediateTable::getCol(int colIndex) {
    vector<string> res = {};
    res.reserve(this->table.size());
    for (auto &col : this->table) {
        res.push_back(col.at(colIndex));
    };
    return res;
}

vector<string> IntermediateTable::getRow(int rowIndex) {
    return this->table.at(rowIndex);
}

int IntermediateTable::createNewCol(const string &colName) {
    this->colNameToIndexMap[colName] = this->currentColCount;
    return this->currentColCount++;
}

vector<vector<string>> IntermediateTable::getTable() {
    return this->table;
}

vector<string> IntermediateTable::getSingleCol(const string &colName) {
    if (this->colNameToIndexMap.find(colName) == this->colNameToIndexMap.end()) {
        throw std::runtime_error("Non-existent column name");
    }
    int colIndex = this->colNameToIndexMap.at(colName);
    return this->getCol(colIndex);
}

vector<vector<string>> IntermediateTable::getCol(
        const vector<string> &colNameVector) {
    vector<vector<string>> res = {};
    res.reserve(this->table.size());
    for (int rowIndex = 0; rowIndex < table.size(); rowIndex++) {
        vector<string> row = {};
        row.reserve(colNameVector.size());
        for (const string &colName : colNameVector) {
            if (this->colNameToIndexMap.find(colName) == this->colNameToIndexMap.end()) {
                throw std::runtime_error("Non-existent column name");
            }
            int colIndex = this->colNameToIndexMap.at((colName));
            row.push_back(this->table.at(rowIndex).at(colIndex));
        }
        res.push_back(row);
    }

    return res;
}
