#include "IntermediateTable.h"

#include <iostream>
#include <stdexcept>

#include "IntermediateTableUtils.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

IntermediateTable::IntermediateTable(bool isTableWildcard)
    : isWildcard(isTableWildcard), isEmpty(true) {}

IntermediateTable::IntermediateTable(const vector<string> &colNames,
                                     vector<vector<unique_ptr<SynonymRes>>> data) {
  for (const string &colName : colNames) {
    IntermediateTable::createNewCol(colName);
  }
  for (const auto &dataRow : data) {
    vector<unique_ptr<SynonymRes>> rowCopy = {};
    for (const auto &datum :dataRow) {
      rowCopy.emplace_back(std::move(datum->clone()));
    }
    this->tableData.emplace_back(std::move(rowCopy));
  }
  this->tableData = std::move(data);
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
  this->colNames.emplace_back(newColName);
  return this->currentColCount++;
}

vector<vector<string>> IntermediateTable::getDataAsStrings() {
  vector<vector<string>> res;
  for (size_t rowIndex = 0; rowIndex < this->tableData.size(); ++rowIndex) {
    auto &synonymDataRow = this->tableData.at(rowIndex);
    vector<string> row{};
    size_t rowSize = synonymDataRow.size();
    for (size_t colIndex = 0; colIndex < rowSize; colIndex++) {
      row.emplace_back(synonymDataRow.at(colIndex)->toString());
    }
    res.emplace_back(row);
  }
  return res;
}

vector<vector<unique_ptr<SynonymRes>>> &IntermediateTable::getTableData() {
  return this->tableData;
}

set<string> IntermediateTable::getColumns(const vector<string> &colNameVector) {
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
    string row;
    for (const string &colName : colNameVector) {
      int colIndex = this->colNameToIndexMap.at(colName);
      row += (row.empty() ? "" : " ") +
             this->tableData.at(rowIndex).at(colIndex)->toString();
    }
    res.insert(row);
  }
  return res;
}

set<string> IntermediateTable::getColumns(
    const vector<pair<string, AttrRef>> &colNameAndAttrRefVector) {
  if (colNameAndAttrRefVector.empty()) {
    return {};
  }

  for (const pair<string, AttrRef>& colNameAndAttrRef : colNameAndAttrRefVector) {
    string colName = colNameAndAttrRef.first;
    // return empty if any column requested does not exist
    if (!this->isColExists(colName)) {
      return {};
    }
  }

  set<string> res = {};
  for (int rowIndex = 0; rowIndex < this->getRowCount(); rowIndex++) {
    string row;
    for (const pair<string, AttrRef>& colNameAndAttrRef : colNameAndAttrRefVector) {
      string colName = colNameAndAttrRef.first;
      AttrRef attrRef = colNameAndAttrRef.second;
      int colIndex = this->colNameToIndexMap.at(colName);
      row += (row.empty() ? "" : " ") +
             this->tableData.at(rowIndex).at(colIndex)->getAttribute(attrRef);
    }
    res.insert(row);
  }
  return res;
}

vector<string> IntermediateTable::getColNames() { return this->colNames; }

int IntermediateTable::getColIndex(const string &colName) {
  if (!isColExists(colName)) {
    return -1;
  }
  return this->colNameToIndexMap.at(colName);
}

bool IntermediateTable::isColExists(const std::string &colName) {
  return this->colNameToIndexMap.find(colName) != this->colNameToIndexMap.end();
}

size_t IntermediateTable::getRowCount() { return this->tableData.size(); }

bool IntermediateTable::isTableWildcard() const { return this->isWildcard; }

bool IntermediateTable::isTableEmpty() const { return this->isEmpty; }

bool IntermediateTable::isTableEmptyAndNotWildcard() const {
  return !this->isTableWildcard() && this->isTableEmpty();
}

IntermediateTable IntermediateTable::join(
    const IntermediateTable &intermediateTable) {
  if (this->isTableWildcard() && intermediateTable.isTableWildcard()) {
    // WILDCARD x WILDCARD = WILDCARD
    return intermediateTable;
  }
  if (this->isTableEmptyAndNotWildcard() ||
      intermediateTable.isTableEmptyAndNotWildcard()) {
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
  return noSharedColumns
             ? getCrossProduct(*this, intermediateTable)
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

  for (auto &row : this->getDataAsStrings()) {
    string rowDataToPrint;
    for (auto &col : row) {
      rowDataToPrint += col + " | ";
    }
    std::cout << rowDataToPrint << std::endl;
  }
}
