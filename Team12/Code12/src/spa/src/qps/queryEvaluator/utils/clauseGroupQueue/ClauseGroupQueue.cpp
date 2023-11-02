#include "ClauseGroupQueue.h"

void ClauseGroupQueue::addClauseGroup(const ClauseGroup& clause) {
  this->clauseGroupQueue.push(clause);
}

IntermediateTable ClauseGroupQueue::evaluate(PKBReader& pkb) {
  TableQueue tableQueue {};
  while (!this->clauseGroupQueue.empty()) {
    ClauseGroup clauseGroup = this->clauseGroupQueue.front();
    tableQueue.addTable(clauseGroup.evaluate(pkb));
    this->clauseGroupQueue.pop();
  }
  return tableQueue.getJoinResult();
}

std::queue<ClauseGroup>& ClauseGroupQueue::getQueue() {
  return this->clauseGroupQueue;
}
