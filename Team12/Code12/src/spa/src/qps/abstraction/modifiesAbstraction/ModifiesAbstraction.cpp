#include "ModifiesAbstraction.h"

/**
 * Modifies abstraction:
 * firstArg: Synonym OR Integer OR Wildcard
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

  vector<pair<string, string>> result =
      pkb.getVariablesModifiedBy(firstArgStmtNumber, StmtType::STMT);

  return IntermediateTableFactory::buildIntermediateTable(
      WILDCARD_KEYWORD, secondArgVarSynonym, result);
}

// Modifies (StmtNumber, VarIdentifier)
IntermediateTable ModifiesAbstraction::evaluateIntegerIdent() {
  string stmtNumber = this->firstArgValue;

  if (pkb.isVariableModifiedBy(this->secondArgValue, stmtNumber)) {
    return IntermediateTableFactory::buildWildcardIntermediateTable();
  }
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Modifies (StmtNumber, _)
IntermediateTable ModifiesAbstraction::evaluateIntegerWildcard() {
  int firstArgStmtNumber = stoi(this->firstArgValue);

  vector<pair<string, string>> result =
      pkb.getVariablesModifiedBy(firstArgStmtNumber, StmtType::STMT);

  if (result.empty()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  return IntermediateTableFactory::buildWildcardIntermediateTable();
}

// Modifies (_, VarSynonym)
IntermediateTable ModifiesAbstraction::evaluateWildcardSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Modifies (_, VarIdentifier)
IntermediateTable ModifiesAbstraction::evaluateWildcardIdent() {
  StmtType firstArgStmtType = getFirstArgStmtType();
  string secondArgIdent = this->secondArgValue;

  vector<string> statementsModifyingVar =
      pkb.getStatementsModifying(secondArgIdent, firstArgStmtType);

  return IntermediateTableFactory::buildSingleColTable(WILDCARD_KEYWORD,
                                                       statementsModifyingVar);
}

// Modifies (_, _)
IntermediateTable ModifiesAbstraction::evaluateWildcardWildcard() {
  return handleSynonymOrWildcardArgs();
}

IntermediateTable ModifiesAbstraction::handleSynonymOrWildcardArgs() {
  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = getFirstArgStmtType();
  string secondArgVarSynonym = this->secondArgValue;

  vector<pair<string, string>> statementsModifiedVar =
      pkb.getAllModifiedVariables(firstArgStmtType);

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      firstArgStmtSynonym, secondArgVarSynonym, statementsModifiedVar);
}
