#include "Query.h"

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

IntermediateTable Query::evalSelectClause(PKBReader& pkb) {
  return this->selectClause->evaluate(pkb);
}

bool Query::operator==(const Query& other) {
  if (selectClause && !this->selectClause->isEquals(*other.selectClause))
    return false;

  for (int i = 0; i < this->clauses.size(); i++) {
    if (!clauses.at(i)->isEquals(*(other.clauses.at(i)))) {
      return false;
    }
  }

  return true;
}
