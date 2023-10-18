#include "Query.h"

#include <cassert>

#include "../intermediateTable/IntermediateTableFactory.h"
#include "qps/clause/selectClause/SelectClause.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

Query::Query(PKBReader &pkb) : pkb(pkb) {}

void Query::addContext(unique_ptr<Context> contextToAdd) {
  this->context = std::move(contextToAdd);
}

void Query::addClause(unique_ptr<Clause> clause) {
  this->clauses.push_back(std::move(clause));
}

void Query::setSynonymToQuery(SynonymsToSelect selectSynonyms) {
  for (auto &synonymArg : selectSynonyms) {
    this->synonymsToQuery.emplace_back(synonymArg->getValue());
  }
  this->selectClause =
      std::make_unique<SelectClause>(std::move(selectSynonyms));
}

set<string> Query::evaluate() {
  // todo 1: query optimisation
  // if at least 1 of selected synonyms exist in table or if table is wildcard,
  // join and return else if cols not exist and not empty, return all select
  // columns else return empty

  // todo 2: abstract out evaluation to evaluator

  assert(selectClause);

  // evaluate SelectClause first
  IntermediateTable currIntermediateTable =
      selectClause->evaluate(*context, pkb);
  if (currIntermediateTable.isTableEmptyAndNotWildcard()) {
    return {};
  }

  // iteratively join results of each clause
  for (unique_ptr<Clause> &clause : clauses) {
    IntermediateTable clauseResult = clause->evaluate(*context, pkb);
    currIntermediateTable = currIntermediateTable.join(clauseResult);
    if (currIntermediateTable.isTableEmptyAndNotWildcard()) {
      // do not continue evaluating once we have an empty table
      return {};
    }
  }

  return currIntermediateTable.getColumns(synonymsToQuery);
}

bool Query::operator==(const Query &other) {
  bool res = this->context->getMap() == other.context->getMap();
  if (!res) return res;

  if (this->synonymsToQuery != other.synonymsToQuery) {
    return false;
  }

  for (int i = 0; i < this->clauses.size(); i++) {
    if (!clauses.at(i)->isEquals(*(other.clauses.at(i)))) {
      return false;
    }
  }

  return true;
}
