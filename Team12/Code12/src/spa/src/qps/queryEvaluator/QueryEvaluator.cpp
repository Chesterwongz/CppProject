#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator(PKBReader& pkb) : pkb(pkb) {}

unordered_set<string> QueryEvaluator::evaluate(unique_ptr<Query>& query) {
  IntermediateTable currIntermediateTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();

  // iteratively join results of each clause
  for (unique_ptr<Clause>& clause : query->clauses) {
    IntermediateTable clauseResult = clause->evaluate(this->pkb);
    currIntermediateTable = currIntermediateTable.join(clauseResult);
    if (currIntermediateTable.isTableEmptyAndNotWildcard()) {
      // do not continue evaluating once we have an empty table
      break;
    }
  }

  bool hasRowsInTable = !currIntermediateTable.isTableEmptyAndNotWildcard();
  if (hasRowsInTable) {
    currIntermediateTable =
        currIntermediateTable.join(query->evalSelectClause(this->pkb));
  }

  auto res = query->selectClause->getQueryResult(currIntermediateTable);
  this->pkb.clearCache();

  return res;
}
