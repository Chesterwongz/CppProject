#include "UsesAbstraction.h"

/**
 * Uses abstraction:
 * firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * secondArg: Synonym OR Identifier OR Wildcard
 */

// Uses (StatementSynonym, VarSynonym)
IntermediateTable UsesAbstraction::evaluateSynonymSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Uses (StatementSynonym, VarIdentifier)
IntermediateTable UsesAbstraction::evaluateSynonymIdent() {
  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = getFirstArgStmtType();
  string secondArgIdent = this->secondArgValue;

  vector<string> statementsUsingVar =
      pkb.getStatementsUsing(secondArgIdent, firstArgStmtType);

  return IntermediateTableFactory::buildSingleColTable(firstArgStmtSynonym,
                                                       statementsUsingVar);
}

// Uses (StatementSynonym, _)
IntermediateTable UsesAbstraction::evaluateSynonymWildcard() {
  return handleSynonymOrWildcardArgs();
}

// Uses (StatementNumber, VarSynonym)
IntermediateTable UsesAbstraction::evaluateIntegerSynonym() {
  int firstArgStmtNumber = stoi(this->firstArgValue);
  string secondArgVarSynonym = this->secondArgValue;

  vector<string> result = pkb.getVariablesUsedBy(firstArgStmtNumber);

  return IntermediateTableFactory::buildSingleColTable(secondArgVarSynonym,
                                                       result);
}

// Uses (StatementNumber, VarIdentifier)
IntermediateTable UsesAbstraction::evaluateIntegerIdent() {
  int firstArgStmtNumber = stoi(this->firstArgValue);
  string secondArgIdent = this->secondArgValue;

  if (pkb.isVariableUsedBy(firstArgStmtNumber, secondArgIdent)) {
    return IntermediateTableFactory::buildWildcardIntermediateTable();
  }
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Uses (StatementNumber, _)
IntermediateTable UsesAbstraction::evaluateIntegerWildcard() {
  int firstArgStmtNumber = stoi(this->firstArgValue);

  vector<string> result = pkb.getVariablesUsedBy(firstArgStmtNumber);

  return IntermediateTableFactory::buildSingleColTable(WILDCARD_KEYWORD,
                                                       result);
}

IntermediateTable UsesAbstraction::handleSynonymOrWildcardArgs() {
  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = getFirstArgStmtType();
  string secondArgVarSynonym = this->secondArgValue;

  vector<pair<string, string>> allStatementsUsingAllVar =
      pkb.getUsesStmtPairs(firstArgStmtType);

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      firstArgStmtSynonym, secondArgVarSynonym, allStatementsUsingAllVar);
}
