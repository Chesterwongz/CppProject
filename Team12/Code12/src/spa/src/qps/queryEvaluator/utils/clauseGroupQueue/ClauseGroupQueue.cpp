#include "ClauseGroupQueue.h"

void ClauseGroupQueue::addClauseGroup(const ClauseGroup& clause) {
  this->clauseGroupQueue.push(clause);
}

IntermediateTable ClauseGroupQueue::evaluate(PKBReader& pkb) {
  TableQueue tableQueue {};
  while (!this->clauseGroupQueue.empty()) {
    ClauseGroup clauseGroup = this->clauseGroupQueue.top();
    tableQueue.addTable(clauseGroup.evaluate(pkb));
    this->clauseGroupQueue.pop();
  }
  return tableQueue.getJoinResult();
}

std::priority_queue<ClauseGroup>& ClauseGroupQueue::getQueue() {
  return this->clauseGroupQueue;
}

// todo(yq) order clause groups based on score
bool operator<(const ClauseGroup& thisGroup, const ClauseGroup& otherGroup) {
  //  return thisGroup.getScore() > otherGroup.getScore();
  return false;
}


