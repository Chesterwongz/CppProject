#include "ClauseGroup.h"

ClauseGroup::ClauseGroup(ClauseUtil::ClauseRefList& clauseList) {
  for (unique_ptr<Clause>& clause : clauseList) {
    this->clauseRefList.emplace_back(clause);
  }
}

ClauseGroup::ClauseGroup(unique_ptr<Clause>& clause) {
  this->clauseRefList.emplace_back(clause);
}

void ClauseGroup::evaluateClauseToTables(PKBReader& pkb) {
  for (const unique_ptr<Clause>& clause : this->clauseRefList) {
    string clauseKey = clause->getKey();
    if (this->evaluatedClauses.find(clauseKey) !=
        this->evaluatedClauses.end()) {
      // ignore clauses we evaluated before
      continue;
    }
    IntermediateTable clauseRes = clause->evaluate(pkb);
    bool isEmpty = clauseRes.isTableEmptyAndNotWildcard();
    this->tableQueue.addTable(std::move(clauseRes));
    this->evaluatedClauses.insert(clauseKey);

    if (isEmpty) {
      // stop evaluation if we get empty table
      break;
    }
  }
}

IntermediateTable ClauseGroup::evaluate(PKBReader& pkb) {
  this->evaluateClauseToTables(pkb);
  return this->tableQueue.getJoinResult();
}
