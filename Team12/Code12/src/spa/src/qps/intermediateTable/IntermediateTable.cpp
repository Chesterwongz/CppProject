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

vector<vector<string>> IntermediateTable::getDataAsStrings() const {
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

TableDataType IntermediateTable::getTableData() const {
  return this->tableData;
}

unordered_set<string> IntermediateTable::getColumns(
    const vector<string> &colNameVector) const {
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
    const SynonymsToSelect &selectSynonyms) const {
  if (selectSynonyms.empty()) {
    return {};
  }

  for (const auto &synonym : selectSynonyms) {
    // return empty if any column requested does not exist
    if (!this->isColExists(synonym->getValue())) {
      return {};
    }
  }

  unordered_set<string> res = {};
  for (int rowIndex = 0; rowIndex < this->getRowCount(); rowIndex++) {
    string row;
    for (const auto &synonym : selectSynonyms) {
      string synonymValue = synonym->getValue();
      AttrRef attrRef = synonym->getAttrRef();
      int colIndex = this->colNameToIndexMap.at(synonymValue);
      assert(this->tableData.at(rowIndex).at(colIndex).isAttrExists(attrRef));
      row += (row.empty() ? "" : " ") +
             this->tableData.at(rowIndex).at(colIndex).getAttribute(attrRef);
    }
    res.insert(row);
  }
  return res;
}

vector<string> IntermediateTable::getColNames() const { return this->colNames; }

int IntermediateTable::getColIndex(const string &colName) const {
  if (!isColExists(colName)) {
    return IntermediateTableUtils::INVALID_COL_INDEX;
  }
  return this->colNameToIndexMap.at(colName);
}

bool IntermediateTable::isColExists(const std::string &colName) const {
  return this->colNameToIndexMap.find(colName) != this->colNameToIndexMap.end();
}

size_t IntermediateTable::getRowCount() const { return this->tableData.size(); }

bool IntermediateTable::isTableWildcard() const { return this->isWildcard; }

bool IntermediateTable::isTableEmpty() const { return this->isEmpty; }

bool IntermediateTable::isTableEmptyAndNotWildcard() const {
  return !this->isTableWildcard() && this->isTableEmpty();
}

IntermediateTable IntermediateTable::join(const IntermediateTable &otherTable) {
  if (this->isTableWildcard() && otherTable.isTableWildcard()) {
    // WILDCARD x WILDCARD = WILDCARD
    return otherTable;
  }
  if (this->isTableEmptyAndNotWildcard() ||
      otherTable.isTableEmptyAndNotWildcard()) {
    // (ANY x EMPTY || EMPTY x ANY) = EMPTY
    return IntermediateTable::makeEmptyTable();
  }
  if (this->isTableWildcard() && !otherTable.isTableWildcard()) {
    // WILDCARD X TABLE_2 = TABLE_2
    return otherTable;
  }
  if (!this->isTableWildcard() && otherTable.isTableWildcard()) {
    // TABLE_1 x WILDCARD = TABLE_1
    return *this;
  }

  pair<vector<int>, vector<int>> sharedColumnIndexes =
      IntermediateTableUtils::getSharedColIndexes(*this, otherTable);
  bool noSharedColumns =
      sharedColumnIndexes.first.empty() && sharedColumnIndexes.second.empty();

  // Cross if no shared columns, inner join if shared columns exists
  return noSharedColumns
             ? IntermediateTableUtils::getCrossProduct(*this, otherTable)
             : IntermediateTableUtils::getInnerJoin(sharedColumnIndexes, *this,
                                                    otherTable);
}

IntermediateTable IntermediateTable::join(
    const IntermediateTable &otherTable,
    const pair<string, AttrRef> &joinColThis,
    const pair<string, AttrRef> &joinColOther) {
  if (this->isTableWildcard() && otherTable.isTableWildcard()) {
    // WILDCARD x WILDCARD = WILDCARD
    return otherTable;
  }
  if (this->isTableEmptyAndNotWildcard() ||
      otherTable.isTableEmptyAndNotWildcard()) {
    // (ANY x EMPTY || EMPTY x ANY) = EMPTY
    return IntermediateTable::makeEmptyTable();
  }
  if (this->isTableWildcard() && !otherTable.isTableWildcard()) {
    // WILDCARD X TABLE_2 = TABLE_2
    return otherTable;
  }
  if (!this->isTableWildcard() && otherTable.isTableWildcard()) {
    // TABLE_1 x WILDCARD = TABLE_1
    return *this;
  }
  return IntermediateTableUtils::getInnerJoinOn(*this, otherTable, joinColThis,
                                                joinColOther);
}

void IntermediateTable::printTable() const {
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

  for (auto &row : this->getTableData()) {
    string rowDataToPrint;
    for (auto &col : row) {
      rowDataToPrint += col.getAttribute(AttrRefEnum::DEFAULT) + "," +
                        col.getAttribute(AttrRefEnum::VALUE_ENUM) + "," +
                        col.getAttribute(AttrRefEnum::VAR_NAME_ENUM) + "," +
                        col.getAttribute(AttrRefEnum::STMT_NUM_ENUM) + "," +
                        col.getAttribute(AttrRefEnum::PROC_NAME_ENUM) + " | ";
    }
    std::cout << rowDataToPrint << std::endl;
  }
}

/**
   * for min heap implementation
 */
bool operator<(const IntermediateTable &thisTable,
               const IntermediateTable &otherTable) {
  return thisTable.getRowCount() > otherTable.getRowCount();
}
