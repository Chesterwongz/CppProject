#include "TableQueue.h"

void TableQueue::addTable(IntermediateTable table) {
  this->tableQueue.push(std::move(table));
}

IntermediateTable TableQueue::getJoinResult() {
  if (this->tableQueue.empty()) {
    return IntermediateTableFactory::buildWildcardIntermediateTable();
  }
  std::vector<IntermediateTable> sortedTables;
  while (!tableQueue.empty()) {
    sortedTables.emplace_back(tableQueue.top());
    tableQueue.pop();
  }

  IntermediateTable finalTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  while (!sortedTables.empty() && sortedTables.back().getRowCount() == 0) {
    IntermediateTable& curr = sortedTables.back();
    if (curr.isTableEmptyAndNotWildcard()) {
      return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    finalTable = finalTable.join(curr);
    sortedTables.pop_back();
  }

  std::unordered_map<string, vector<std::reference_wrapper<IntermediateTable>>>
      columnToTablesMap;
  std::unordered_set<IntermediateTable*> joinedTables;
  for (auto& table : sortedTables) {
    for (const auto& colName : table.getColNames()) {
      columnToTablesMap[colName].emplace_back(table);
    }
  }
  while (!sortedTables.empty()) {
    if (finalTable.isTableEmpty()) {
      finalTable = sortedTables.back();
      joinedTables.insert(&finalTable);
      sortedTables.pop_back();
      continue;
    }
    // Find all tables that share columns with finalTable and join them.
    vector<string> colNames = finalTable.getColNames();
    for (const auto& colName : colNames) {
      auto& tablesWithCol = columnToTablesMap[colName];
      for (IntermediateTable& otherTable : tablesWithCol) {
        if (joinedTables.count(&otherTable)) continue;

        finalTable = finalTable.join(otherTable);
        joinedTables.insert(&otherTable);

        // Update the column mapping for the joined table.
//        for (const auto& newColName : otherTable.getColNames()) {
//          columnToTablesMap[newColName].emplace_back(finalTable);
//        }
      }
    }

    // Remove joined tables from the sorted list.
    sortedTables.erase(
        std::remove_if(sortedTables.begin(), sortedTables.end(),
                       [&joinedTables](IntermediateTable& table) {
                         return joinedTables.count(&table) > 0;
                       }),
        sortedTables.end());
  }

  // 1. get smallest two tables
  // 2. join
  // 3. push into queue
  //  while (this->tableQueue.size() > 1) {
  //    IntermediateTable smallest = this->tableQueue.top();
  //    this->tableQueue.pop();
  //    IntermediateTable secondSmallest = this->tableQueue.top();
  //    this->tableQueue.pop();
  //    // if any table is empty, stop evaluation and return empty table
  //    if (smallest.isTableEmptyAndNotWildcard() ||
  //        secondSmallest.isTableEmptyAndNotWildcard()) {
  //      return IntermediateTableFactory::buildEmptyIntermediateTable();
  //    }
  //    this->tableQueue.push(smallest.join(secondSmallest));
  //  }
  //  IntermediateTable final = tableQueue.top();
  //  tableQueue.pop();
  return finalTable;
}

/**
 * for min heap implementation
 */
bool operator<(const IntermediateTable& thisTable,
               const IntermediateTable& otherTable) {
  //  if (thisTable.getRowCount() == 0) return true;
  //  if (otherTable.getRowCount() == 0) return false;
  //
  //  const vector<string>& thisColNames = thisTable.getColNames();
  //  const vector<string>& otherColNames = otherTable.getColNames();
  //  bool isCurrLexicoSmaller =
  //      std::lexicographical_compare(thisColNames.begin(), thisColNames.end(),
  //                                   otherColNames.begin(),
  //                                   otherColNames.end());
  //  if (isCurrLexicoSmaller) {
  //    return true;
  //  }
  //
  //  bool isCurrLexicoLarger =
  //      std::lexicographical_compare(otherColNames.begin(),
  //      otherColNames.end(),
  //                                   thisColNames.begin(),
  //                                   thisColNames.end());
  //  if (isCurrLexicoLarger) {
  //    return false;
  //  }
  // If column names are the same, then sort by row count in descending order
  return thisTable.getRowCount() < otherTable.getRowCount();
}
