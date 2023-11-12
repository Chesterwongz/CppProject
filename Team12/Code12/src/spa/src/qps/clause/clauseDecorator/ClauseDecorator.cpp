#include "ClauseDecorator.h"

set<string> ClauseDecorator::getClauseSynonyms() {
  return wrapeeClause->getClauseSynonyms();
}

ClauseKey ClauseDecorator::getKey() {
  return wrapeeClause->getKey();
}
