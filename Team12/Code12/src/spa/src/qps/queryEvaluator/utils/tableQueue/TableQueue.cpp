#include "TableQueue.h"

void TableQueue::addTable(IntermediateTable table) {
  this->tableQueue.push(std::move(table));
}

IntermediateTable TableQueue::getJoinResult() {
  if (this->tableQueue.empty()) {
    return IntermediateTableFactory::buildWildcardIntermediateTable();
  }
  //   1. get smallest two tables
  //   2. join
  //   3. push into queue
  while (this->tableQueue.size() > 1) {
    IntermediateTable smallest = this->tableQueue.top();
    this->tableQueue.pop();
    IntermediateTable secondSmallest = this->tableQueue.top();
    this->tableQueue.pop();
    // if any table is empty, stop evaluation and return empty table
    if (smallest.isTableEmptyAndNotWildcard() ||
        secondSmallest.isTableEmptyAndNotWildcard()) {
      return IntermediateTableFactory::buildEmptyIntermediateTable();
    }
    this->tableQueue.push(smallest.join(secondSmallest));
  }
  IntermediateTable final = tableQueue.top();
  tableQueue.pop();
  return final;
}

/**
 * for min heap implementation
 */
bool operator<(const IntermediateTable& thisTable,
               const IntermediateTable& otherTable) {
  if (thisTable.getRowCount() <= TableQueue::THRESHOLD) return false;
  if (otherTable.getRowCount() <= TableQueue::THRESHOLD) return true;

  const vector<string>& thisColNames = thisTable.getColNames();
  const vector<string>& otherColNames = otherTable.getColNames();
  bool isCurrLexicoSmaller =
      std::lexicographical_compare(thisColNames.begin(), thisColNames.end(),
                                   otherColNames.begin(), otherColNames.end());
  if (isCurrLexicoSmaller) {
    return true;
  }

  bool isCurrLexicoLarger =
      std::lexicographical_compare(otherColNames.begin(), otherColNames.end(),
                                   thisColNames.begin(), thisColNames.end());
  if (isCurrLexicoLarger) {
    return false;
  }
  // If column names are the same, then sort by row count in descending order
  return thisTable.getRowCount() > otherTable.getRowCount();
}
