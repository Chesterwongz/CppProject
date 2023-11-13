#include "Query.h"

void Query::addNotClause(unique_ptr<NotDecorator> notClause) {
  assert(
      this->selectClause);  // selectClause already added with setSynonymToQuery
  this->selectClause->addSynonymsInOtherClause(notClause->getClauseSynonyms());
  this->notClauses.push_back(std::move(notClause));
}

void Query::addClause(unique_ptr<Clause> clause) {
  assert(
      this->selectClause);  // selectClause already added with setSynonymToQuery
  this->selectClause->addSynonymsInOtherClause(clause->getClauseSynonyms());
  this->clauses.push_back(std::move(clause));
}

void Query::setSynonymToQuery(SynonymsToSelect selectSynonyms) {
  this->selectClause =
      SelectClauseFactory::createSelectClause(std::move(selectSynonyms));
}

IntermediateTable Query::evalSelectClause(PKBReader& pkb, ClauseCache& cache) {
  return this->selectClause->evaluate(pkb, cache);
}

bool Query::operator==(const Query& other) {
  if (selectClause && !this->selectClause->isEquals(*other.selectClause))
    return false;

  for (int i = 0; i < this->notClauses.size(); i++) {
    if (!notClauses.at(i)->isEquals(*(other.notClauses.at(i)))) {
      return false;
    }
  }

  for (int i = 0; i < this->clauses.size(); i++) {
    if (!clauses.at(i)->isEquals(*(other.clauses.at(i)))) {
      return false;
    }
  }

  return true;
}

set<string> Query::getSelectedSynonyms() {
  return this->selectClause->getClauseSynonyms();
}

unordered_set<string> Query::getQueryResult(IntermediateTable& finalTable) {
  return this->selectClause->getQueryResult(finalTable);
}
