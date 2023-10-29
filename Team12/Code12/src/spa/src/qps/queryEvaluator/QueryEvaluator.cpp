#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator(PKBReader& pkb) : pkb(pkb) {}

unordered_set<string> QueryEvaluator::evaluate(unique_ptr<Query>& query) {
  unique_ptr<IClauseGrouper> grouper =
      std::make_unique<ClauseGrouper>(query->clauses);

  // group and evaluate non-select clauses
  ClauseGroupQueue groups = grouper->groupClauses();
  IntermediateTable clauseResults = groups.evaluate(this->pkb);

  // evaluate select clause
  IntermediateTable finalTable =
      clauseResults.join(query->evalSelectClause(this->pkb));

  this->pkb.clearCache();
  return query->selectClause->getQueryResult(finalTable);
}
