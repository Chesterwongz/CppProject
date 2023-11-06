#include "IntermediateTable.h"

#include <algorithm>
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

const TableDataType &IntermediateTable::getTableData() const {
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
             this->tableData.at(rowIndex).at(colIndex).get().toString();
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

  // return empty if any column requested does not exist
  if (std::any_of(selectSynonyms.begin(), selectSynonyms.end(),
                  [this](const auto &synonym) {
                    return !this->isColExists(synonym->getValue());
                  })) {
    return {};
  }

  unordered_set<string> res = {};
  for (int rowIndex = 0; rowIndex < this->getRowCount(); rowIndex++) {
    string row;
    for (const auto &synonym : selectSynonyms) {
      string synonymValue = synonym->getValue();
      AttrRef attrRef = synonym->getAttrRef();
      int colIndex = this->colNameToIndexMap.at(synonymValue);
      assert(this->tableData.at(rowIndex).at(colIndex).get().isAttrExists(
          attrRef));
      row +=
          (row.empty() ? "" : " ") +
          this->tableData.at(rowIndex).at(colIndex).get().getAttribute(attrRef);
    }
    res.insert(std::move(row));
  }
  return res;
}

const vector<string> &IntermediateTable::getColNames() const {
  return colNames;
}

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
             : IntermediateTableUtils::getNaturalJoin(sharedColumnIndexes,
                                                      *this, otherTable);
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

IntermediateTable IntermediateTable::getDifference(
    const IntermediateTable &otherTable) {
  if (otherTable.isTableWildcard()) {
    // ANY - WILDCARD = EMPTY
    return IntermediateTable::makeEmptyTable();
  }

  if (this->isTableEmpty() || otherTable.isTableEmpty()) {
    // EMPTY - ANY = EMPTY
    // ANY - EMPTY = ANY
    return *this;
  }

  // must have same number of cols
  assert(colNames.size() == otherTable.getColNames().size());
  for (int i = 0; i < colNames.size(); i++) {
    // both tables cols must be the same
    assert(colNames[i] == otherTable.getColNames()[i]);
  }

  TableDataType otherTableData = otherTable.getTableData();
  unordered_map<string, vector<TableRowType>> t2Mapping;
  for (const TableRowType &otherTableRow : otherTableData) {
    t2Mapping[IntermediateTableUtils::getRowKey(otherTableRow)].emplace_back(
        otherTableRow);
  }

  TableDataType newTableData;
  for (TableRowType &row : this->tableData) {
    if (t2Mapping.find(IntermediateTableUtils::getRowKey(row)) !=
        t2Mapping.end()) {
      continue;
    } else {
      newTableData.emplace_back(std::move(row));
    }
  }

  return IntermediateTable(colNames, newTableData);
}

void IntermediateTable::printTable() const {
  std::cout << "table: " << std::endl;
  if (this->isWildcard || this->isEmpty) {
    std::cout << (isWildcard ? "WILDCARD" : "EMPTY") << std::endl;
    return;
  }

  string colNamesToPrint;
  for (auto &colName : this->getColNames()) {
    colNamesToPrint += colName + IntermediateTableUtils::TABLE_KEY_DELIMITER;
  }
  std::cout << colNamesToPrint << std::endl;

  for (const auto &row : this->getTableData()) {
    string rowDataToPrint;
    for (auto &col : row) {
      rowDataToPrint += col.get().getAttribute(ATTR_REF_DEFAULT) + "," +
                        col.get().getAttribute(ATTR_REF_VALUE) + "," +
                        col.get().getAttribute(ATTR_REF_VAR_NAME) + "," +
                        col.get().getAttribute(ATTR_REF_STMT_NUMBER) + "," +
                        col.get().getAttribute(ATTR_REF_PROC_NAME) +
                        IntermediateTableUtils::TABLE_KEY_DELIMITER;
    }
    std::cout << rowDataToPrint << std::endl;
  }
}
