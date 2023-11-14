#include "ClauseGroupQueue.h"

void ClauseGroupQueue::addClauseGroup(const ClauseGroup& clause) {
  this->clauseGroupQueue.push(clause);
}

IntermediateTable ClauseGroupQueue::evaluate(
    PKBReader& pkb, ClauseCache& cache, const set<string>& selectedSynonyms) {
  TableQueue tableQueue {};
  while (!this->clauseGroupQueue.empty()) {
    ClauseGroup clauseGroup = this->clauseGroupQueue.front();
    IntermediateTable clauseGroupRes =
        clauseGroup.evaluate(pkb, cache, selectedSynonyms);

    if (clauseGroupRes.isTableEmptyAndNotWildcard()) {
      // stop evaluation if we get empty table
      return clauseGroupRes;
    }

    tableQueue.addTable(std::move(clauseGroupRes));
    this->clauseGroupQueue.pop();
  }
  return tableQueue.getJoinResult();
}

std::queue<ClauseGroup>& ClauseGroupQueue::getQueue() {
  return this->clauseGroupQueue;
}
