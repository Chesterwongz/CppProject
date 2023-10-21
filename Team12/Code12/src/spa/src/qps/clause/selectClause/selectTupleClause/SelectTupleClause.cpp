#include "SelectTupleClause.h"

#include <cassert>

#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable SelectTupleClause::evaluate(PKBReader &pkb) {
  assert(!this->synonymsToSelect.empty());

  IntermediateTable result =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  for (auto &synonymArg : this->synonymsToSelect) {
    IntermediateTable possibleValues = getAllPossibleValues(pkb, synonymArg);
    result = result.join(possibleValues);
    if (result.isTableEmptyAndNotWildcard()) {
      return result;
    }
  }
  return result;
}

IntermediateTable SelectTupleClause::getAllPossibleValues(
    PKBReader &pkb, unique_ptr<SynonymArg> &synonymArg) {
  string synonymValue = synonymArg->getValue();
  Entity entity = synonymArg->getEntityType();
  vector<string> results;

  bool isStmtEntity =
      STATEMENT_ENTITIES.find(entity) != STATEMENT_ENTITIES.end();

  if (isStmtEntity) {
    StmtType stmtType = StmtEntityToStatementType.at(entity);
    results = pkb.getAllStmtsOf(stmtType);
  } else {
    results = SelectTupleClause::evaluatorFuncMap.at(entity)(pkb);
  }
  return IntermediateTableFactory::buildSingleColTable(synonymValue, results);
}

bool SelectTupleClause::isEquals(const Clause &other) {
  const auto *otherSelect = dynamic_cast<const SelectTupleClause *>(&other);
  if (!otherSelect) return false;

  if (this->synonymsToSelect.size() != otherSelect->synonymsToSelect.size()) {
    return false;
  }

  for (size_t i = 0; i < this->synonymsToSelect.size(); i++) {
    if (this->synonymsToSelect.at(i)->getValue() !=
        otherSelect->synonymsToSelect.at(i)->getValue()) {
      return false;
    }
  }

  return true;
}

unordered_set<string> SelectTupleClause::getQueryResult(
    IntermediateTable &intermediateTable) {
  return intermediateTable.getColumns(this->synonymsToSelect);
}
