#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator(PKBReader& pkb) : pkb(pkb) {}

unordered_set<string> QueryEvaluator::evaluate(unique_ptr<Query>& query) {
  // group and evaluate non-select clauses
  ClauseGroupQueue groups = ClauseGrouper::groupClauses(query->clauses);
  IntermediateTable clauseResults = groups.evaluate(this->pkb);

  // evaluate select clause
  IntermediateTable finalTable =
      clauseResults.join(query->evalSelectClause(this->pkb));

  this->pkb.clearCache();
  return query->selectClause->getQueryResult(finalTable);
}
