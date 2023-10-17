#include "ModifiesAbstraction.h"

/**
 * Modifies abstraction:
 * firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * secondArg: Synonym OR Identifier OR Wildcard
 */

// Modifies (StmtSynonym, VarSynonym)
IntermediateTable ModifiesAbstraction::evaluateSynonymSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Modifies (StmtSynonym, VarIdentifier)
IntermediateTable ModifiesAbstraction::evaluateSynonymIdent() {
  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = getFirstArgStmtType();
  string secondArgIdent = this->secondArgValue;

  vector<string> statementsModifyingVar =
      pkb.getStatementsModifying(secondArgIdent, firstArgStmtType);

  return IntermediateTableFactory::buildSingleColTable(firstArgStmtSynonym,
                                                       statementsModifyingVar);
}

// Modifies (StmtSynonym, _)
IntermediateTable ModifiesAbstraction::evaluateSynonymWildcard() {
  return handleSynonymOrWildcardArgs();
}

// Modifies (StmtNumber, VarSynonym)
IntermediateTable ModifiesAbstraction::evaluateIntegerSynonym() {
  int firstArgStmtNumber = stoi(this->firstArgValue);
  string secondArgVarSynonym = this->secondArgValue;

  vector<string> result = pkb.getVariablesModifiedBy(firstArgStmtNumber);

  return IntermediateTableFactory::buildSingleColTable(secondArgVarSynonym,
                                                       result);
}

// Modifies (StmtNumber, VarIdentifier)
IntermediateTable ModifiesAbstraction::evaluateIntegerIdent() {
  int firstArgStmtNumber = std::stoi(this->firstArgValue);
  string secondArgIdent = this->secondArgValue;

  if (pkb.isVariableUsedBy(firstArgStmtNumber, secondArgIdent)) {
    return IntermediateTableFactory::buildWildcardIntermediateTable();
  }
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Modifies (StmtNumber, _)
IntermediateTable ModifiesAbstraction::evaluateIntegerWildcard() {
  int firstArgStmtNumber = stoi(this->firstArgValue);

  vector<string> result = pkb.getVariablesModifiedBy(firstArgStmtNumber);

  return IntermediateTableFactory::buildSingleColTable(WILDCARD_KEYWORD,
                                                       result);
}

IntermediateTable ModifiesAbstraction::handleSynonymOrWildcardArgs() {
  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = getFirstArgStmtType();
  string secondArgVarSynonym = this->secondArgValue;

  vector<pair<string, string>> statementsModifiedVar =
      pkb.getModifiesStmtPairs(firstArgStmtType);

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      firstArgStmtSynonym, secondArgVarSynonym, statementsModifiedVar);
}
