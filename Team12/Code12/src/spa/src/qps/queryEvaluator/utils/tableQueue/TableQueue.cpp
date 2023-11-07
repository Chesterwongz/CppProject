#include "TableQueue.h"

void TableQueue::addTable(IntermediateTable table) {
  this->tableQueue.push(std::move(table));
}

IntermediateTable TableQueue::getJoinResult() {
  if (this->tableQueue.empty()) {
    return IntermediateTableFactory::buildWildcardIntermediateTable();
  }
  IntermediateTable finalTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  std::vector<IntermediateTable> sortedTables;
  while (!tableQueue.empty()) {
    if (tableQueue.top().isTableEmptyAndNotWildcard()) {
      return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    if (finalTable.getRowCount() == 0) {
      finalTable = finalTable.join(tableQueue.top());
    } else {
      sortedTables.emplace_back(tableQueue.top());
    }
    tableQueue.pop();
  }

  std::unordered_map<string, vector<std::reference_wrapper<IntermediateTable>>>
      columnToTablesMap;
  for (auto& table : sortedTables) {
    for (const auto& colName : table.getColNames()) {
      columnToTablesMap[colName].emplace_back(table);
    }
  }

  std::unordered_set<IntermediateTable*> joinedTables;
  while (!sortedTables.empty()) {
    // Find all tables that share columns with finalTable and join them.
    for (const auto& colName : finalTable.getColNames()) {
      auto& tablesWithCol = columnToTablesMap[colName];
      for (IntermediateTable& otherTable : tablesWithCol) {
        if (otherTable.isTableEmpty()) continue;

        finalTable = finalTable.join(otherTable);
        otherTable = IntermediateTableFactory::buildEmptyIntermediateTable();
      }
    }

    // Remove joined tables from the sorted list.
    sortedTables.erase(
        std::remove_if(sortedTables.begin(), sortedTables.end(),
                       [](IntermediateTable& table) {
                         return table.isTableEmpty();
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
  return thisTable.getRowCount() > otherTable.getRowCount();
}
