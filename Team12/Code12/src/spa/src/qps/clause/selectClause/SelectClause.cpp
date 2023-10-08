#include "SelectClause.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

SelectClause::SelectClause(SynonymsToSelect synonymsToSelect)
    : synonymsToSelect(std::move(synonymsToSelect)) {}

IntermediateTable SelectClause::evaluate(Context &context, PKBReader &pkb) {
  if (this->synonymsToSelect.empty()) {
    throw QPSInvalidQueryException(QPS_INVALID_QUERY_NO_SELECT_SYNONYM);
  }
  IntermediateTable result =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  for (auto &synonymArg : this->synonymsToSelect) {
    IntermediateTable possibleValues =
        getAllPossibleValues(context, pkb, synonymArg);
    result = result.join(possibleValues);
    if (result.isTableEmptyAndNotWildcard()) {
      return result;
    }
  }
  return result;
}

IntermediateTable SelectClause::getAllPossibleValues(
    Context &context, PKBReader &pkb,
    unique_ptr<AbstractArgument> &synonymArg) {
  string synonymValue = synonymArg->getValue();
  Entity entity = context.getTokenEntity(synonymValue);
  set<string> results;

  bool isStmtEntity =
      STATEMENT_ENTITIES.find(entity) != STATEMENT_ENTITIES.end();

  if (isStmtEntity) {
    StmtType stmtType = StmtEntityToStatementType.at(entity);
    results = pkb.getStatement(stmtType);
  } else {
    results = evaluatorFuncMap[entity](pkb);
  }
  return IntermediateTableFactory::buildIntermediateTable(synonymValue,
                                                          results);
}

bool SelectClause::isEquals(const Clause &other) {
  const auto *otherSelect = dynamic_cast<const SelectClause *>(&other);
  if (!otherSelect) return false;

  return this->synonymsToSelect == otherSelect->synonymsToSelect;
}
