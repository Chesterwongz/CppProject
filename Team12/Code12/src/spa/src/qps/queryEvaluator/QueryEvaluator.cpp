#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator(PKBReader& pkb) : pkb(pkb) {}

unordered_set<string> QueryEvaluator::evaluate(unique_ptr<Query>& query) {
  unique_ptr<IClauseGrouper> grouper =
      std::make_unique<ClauseGrouper>(query->clauses);

  // group and evaluate non-select clauses
  ClauseGroupQueue groups = grouper->groupClauses();
  IntermediateTable clauseResults =
      groups.evaluate(this->pkb, this->cache, query->getSelectedSynonyms());

  for (unique_ptr<NotDecorator>& notClause : query->notClauses) {
    notClause->setCurrentTable(clauseResults);
    IntermediateTable res = notClause->BaseClause::evaluate(pkb, cache);
    clauseResults = clauseResults.join(res);
  }

  // evaluate select clause
  IntermediateTable selectClauseRes =
      query->evalSelectClause(this->pkb, this->cache);
  IntermediateTable finalTable = clauseResults.join(selectClauseRes);

  this->pkb.clearCache();
  unordered_set<string> finalRes = query->getQueryResult(finalTable);
  this->cache.clearCache();

  return finalRes;
}
