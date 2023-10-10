#include "Query.h"

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
  unique_ptr<SelectClause> selectClause =
      std::make_unique<SelectClause>(std::move(selectSynonyms));
  this->addClause(std::move(selectClause));
}

set<string> Query::evaluate() {
  // todo 1: query optimisation
  // if at least 1 of selected synonyms exist in table or if table is wildcard,
  // join and return else if cols not exist and not empty, return all select
  // columns else return empty

  // todo 2: abstract out evaluation to evaluator

  if (clauses.empty()) {
    throw QPSInvalidQueryException(QPS_INVALID_QUERY_NO_CLAUSES);
  }

  // iteratively join results of each clause
  IntermediateTable currIntermediateTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();
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
