#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator(PKBReader& pkb) : pkb(pkb) {}

unordered_set<string> QueryEvaluator::evaluate(unique_ptr<Query>& query) {
  // iteratively evaluate all non-select clause
  for (unique_ptr<Clause>& clause : query->clauses) {
    IntermediateTable clauseResult = clause->evaluate(this->pkb);
    if (clauseResult.isTableEmptyAndNotWildcard()) {
      // do not continue evaluating once we have an empty table
      return query->selectClause->getQueryResult(clauseResult);
    }
    this->tableQueue.push(std::move(clauseResult));
  }

  IntermediateTable finalTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();

  // eval select clause
  this->tableQueue.push(std::move(query->evalSelectClause(this->pkb)));

  // do joining
  finalTable = this->getJoinResult();

  this->pkb.clearCache();
  return query->selectClause->getQueryResult(finalTable);
}

IntermediateTable QueryEvaluator::getJoinResult() {
  if (this->tableQueue.empty()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  // 1. get smallest two tables
  // 2. join
  // 3. push into queue
  while (this->tableQueue.size() > 1) {
    IntermediateTable smallest = this->tableQueue.top();
    this->tableQueue.pop();
    IntermediateTable secondSmallest = this->tableQueue.top();
    this->tableQueue.pop();
    this->tableQueue.push(smallest.join(secondSmallest));
  }
  IntermediateTable final = tableQueue.top();
  tableQueue.pop();
  return final;
}
