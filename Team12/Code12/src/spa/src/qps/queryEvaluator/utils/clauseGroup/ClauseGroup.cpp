#include "ClauseGroup.h"

ClauseGroup::ClauseGroup(ClauseUtil::ClauseRefList & clauseList) {
  for (unique_ptr<Clause> &clause : clauseList) {
    // todo(yq) update group score after each clause is added
    // this->score += clause->getScore();
    this->clauseRefList.emplace_back(clause);
  }
}

ClauseGroup::ClauseGroup(unique_ptr<Clause>& clause) {
  // todo(yq) update group score for single clause added
  // this->score += clause->getScore();
  this->clauseRefList.emplace_back(clause);
}


void ClauseGroup::evaluateClauseToTables(PKBReader& pkb) {
  for (const unique_ptr<Clause>& clause : this->clauseRefList) {
    tableQueue.addTable(clause->evaluate(pkb));
  }
}

IntermediateTable ClauseGroup::evaluate(PKBReader& pkb) {
  this->evaluateClauseToTables(pkb);
  return this->tableQueue.getJoinResult();
}
