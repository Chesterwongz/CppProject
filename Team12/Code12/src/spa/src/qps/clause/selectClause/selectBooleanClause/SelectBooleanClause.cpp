#include "SelectBooleanClause.h"

#include <cassert>

#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable SelectBooleanClause::evaluate(PKBReader &pkb) {
  assert(this->synonymsToSelect.empty());
  return IntermediateTableFactory::buildWildcardIntermediateTable();
}

bool SelectBooleanClause::isEquals(const IClause& other) {
  return dynamic_cast<const SelectBooleanClause *>(&other);
}

unordered_set<string> SelectBooleanClause::getQueryResult(
    IntermediateTable &intermediateTable) {
  return intermediateTable.isTableEmptyAndNotWildcard()
             ? SelectBooleanClauseUtils::FALSE_RESULT
             : SelectBooleanClauseUtils::TRUE_RESULT;
}

set<string> SelectBooleanClause::getClauseSynonyms() {
  return {};
}
