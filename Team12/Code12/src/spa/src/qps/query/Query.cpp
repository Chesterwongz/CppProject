#include "Query.h"

#include <cassert>

#include "../intermediateTable/IntermediateTableFactory.h"
#include "qps/clause/selectClause/ISelectClause.h"
#include "qps/clause/selectClause/SelectClauseFactory.h"
#include "qps/clause/selectClause/selectTupleClause/SelectTupleClause.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

Query::Query(PKBReader &pkb) : pkb(pkb) {}

void Query::addClause(unique_ptr<Clause> clause) {
  this->clauses.push_back(std::move(clause));
}


void Query::setSynonymToQuery(SynonymsToSelect selectSynonyms) {
  this->selectClause =
      SelectClauseFactory::buildSelectClause(std::move(selectSynonyms));
}

unordered_set<string> Query::evaluate() {
  // todo 1: query optimisation
  // if at least 1 of selected synonyms exist in table or if table is wildcard,
  // join and return else if cols not exist and not empty, return all select
  // columns else return empty

  // todo 2: abstract out evaluation to evaluator
  IntermediateTable currIntermediateTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();

  // iteratively join results of each clause
  for (unique_ptr<Clause> &clause : clauses) {
    IntermediateTable clauseResult = clause->evaluate(pkb);
    currIntermediateTable = currIntermediateTable.join(clauseResult);
    if (currIntermediateTable.isTableEmptyAndNotWildcard()) {
      // do not continue evaluating once we have an empty table
      return {};
    }
  }

  assert(selectClause);
  currIntermediateTable.join(selectClause->evaluate(pkb));
  if (currIntermediateTable.isTableEmptyAndNotWildcard()) {
    return {};
  }

  return selectClause->getQueryResult(currIntermediateTable);
}

bool Query::operator==(const Query &other) {
  if (selectClause && !this->selectClause->isEquals(*other.selectClause))
    return false;

  for (int i = 0; i < this->clauses.size(); i++) {
    if (!clauses.at(i)->isEquals(*(other.clauses.at(i)))) {
      return false;
    }
  }

  return true;
}
