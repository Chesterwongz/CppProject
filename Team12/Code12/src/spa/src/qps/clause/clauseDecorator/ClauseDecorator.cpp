#include "ClauseDecorator.h"

vector<const AbstractArgument*> ClauseDecorator::getAllArguments() {
  return wrapeeClause->getAllArguments();
}

set<string> ClauseDecorator::getClauseSynonyms() {
  return wrapeeClause->getClauseSynonyms();
}

string ClauseDecorator::getKey() { return wrapeeClause->getKey(); }
