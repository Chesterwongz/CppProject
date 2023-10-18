#include "IntermediateTable.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "IntermediateTableUtils.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

IntermediateTable::IntermediateTable(bool isTableWildcard)
    : isWildcard(isTableWildcard), isEmpty(true) {}

IntermediateTable::IntermediateTable(const vector<string> &colNames,
                                     TableDataType data) {
  for (const string &colName : colNames) {
    IntermediateTable::createNewCol(colName);
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
  this->colNameToIndexMap[newColName] = this->currentColCount;
  this->colNames.emplace_back(newColName);
  return this->currentColCount++;
}

vector<vector<string>> IntermediateTable::getDataAsStrings() {
  vector<vector<string>> res;
  for (const TableRowType &synonymDataRow : this->tableData) {
    vector<string> row = {};
    row.reserve(synonymDataRow.size());
    for (const SynonymRes &synonymRes : synonymDataRow) {
      row.emplace_back(synonymRes.toString());
    }
    res.emplace_back(row);
  }
  return res;
}

TableDataType IntermediateTable::getTableData() { return this->tableData; }

unordered_set<string> IntermediateTable::getColumns(
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

  unordered_set<string> res = {};
  for (int rowIndex = 0; rowIndex < this->getRowCount(); rowIndex++) {
    string row;
    for (const string &colName : colNameVector) {
      int colIndex = this->colNameToIndexMap.at(colName);
      row += (row.empty() ? "" : " ") +
             this->tableData.at(rowIndex).at(colIndex).toString();
    }
    res.insert(row);
  }
  return res;
}

unordered_set<string> IntermediateTable::getColumns(
    const vector<pair<string, AttrRef>> &colNameAndAttrRefVector) {
  if (colNameAndAttrRefVector.empty()) {
    return {};
  }

  for (auto [colName, attrRef] : colNameAndAttrRefVector) {
    // return empty if any column requested does not exist
    if (!this->isColExists(colName)) {
      return {};
    }
  }

  unordered_set<string> res = {};
  for (int rowIndex = 0; rowIndex < this->getRowCount(); rowIndex++) {
    string row;
    for (auto &[colName, attrRef] : colNameAndAttrRefVector) {
      int colIndex = this->colNameToIndexMap.at(colName);
      assert(this->tableData.at(rowIndex).at(colIndex).isAttrExists(attrRef));
      row += (row.empty() ? "" : " ") +
             this->tableData.at(rowIndex).at(colIndex).getAttribute(attrRef);
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
      IntermediateTableUtils::getSharedColIndexes(*this, intermediateTable);
  bool noSharedColumns =
      sharedColumnIndexes.first.empty() && sharedColumnIndexes.second.empty();

  // Cross if no shared columns, inner join if shared columns exists
  return noSharedColumns
             ? IntermediateTableUtils::getCrossProduct(*this, intermediateTable)
             : IntermediateTableUtils::getInnerJoin(sharedColumnIndexes, *this,
                                                    intermediateTable);
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
