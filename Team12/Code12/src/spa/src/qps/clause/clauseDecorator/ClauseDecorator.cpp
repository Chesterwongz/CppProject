#include "ClauseDecorator.h"

set<string> ClauseDecorator::getClauseSynonyms() {
  return wrapeeClause->getClauseSynonyms();
}

string ClauseDecorator::getKey() { return wrapeeClause->getKey(); }
