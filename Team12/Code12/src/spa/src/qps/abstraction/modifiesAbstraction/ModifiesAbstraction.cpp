#include "ModifiesAbstraction.h"

#include <unordered_set>

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
  string firstArgSynonym = this->firstArgValue;
  bool isFirstArgProcedure =
      this->context.getTokenEntity(firstArgSynonym) == PROCEDURE_ENTITY;
  string secondArgVarName = this->secondArgValue;

  vector<string> result;
  // Modifies(procSynonym, *) and Modifies(stmtSynonym, *) has different APIs
  if (isFirstArgProcedure) {
    result = pkb.getProcModifying(secondArgVarName);
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    result = pkb.getStatementsModifying(secondArgVarName, firstArgStmtType);
  }
  return IntermediateTableFactory::buildSingleColTable(firstArgSynonym, result);
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

// Modifies (ProcName, VarSynonym)
IntermediateTable ModifiesAbstraction::evaluateIdentSynonym() {
  return handleProcNameWithVarSynonymOrWildcard();
}

// Modifies (ProcName, VarName)
IntermediateTable ModifiesAbstraction::evaluateIdentIdent() {
  string firstArgProcName = this->firstArgValue;
  string secondArgVarName = this->secondArgValue;
  bool isProcModifyingVar =
      pkb.isVariableModifiedByProc(firstArgProcName, secondArgVarName);

  return isProcModifyingVar
             ? IntermediateTableFactory::buildWildcardIntermediateTable()
             : IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Modifies (ProcName, _)
IntermediateTable ModifiesAbstraction::evaluateIdentWildcard() {
  return handleProcNameWithVarSynonymOrWildcard();
}

// Modifies (StmtNumber, VarIdentifier)
IntermediateTable ModifiesAbstraction::evaluateIntegerIdent() {
  int firstArgStmtNumber = std::stoi(this->firstArgValue);
  string secondArgIdent = this->secondArgValue;

  if (pkb.isVariableModifiedBy(firstArgStmtNumber, secondArgIdent)) {
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
  string firstArgSynonym = this->firstArgValue;
  bool isFirstArgProcedure =
      this->context.getTokenEntity(firstArgSynonym) == PROCEDURE_ENTITY;
  string secondArgVarSynonym = this->secondArgValue;

  // Modifies(procSynonym, *) and Modifies(stmtSynonym, *) has different APIs
  vector<pair<string, string>> result;
  if (isFirstArgProcedure) {
    result = pkb.getModifiesProcPairs();
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    result = pkb.getModifiesStmtPairs(firstArgStmtType);
  }

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      firstArgSynonym, secondArgVarSynonym, result);
}

IntermediateTable
ModifiesAbstraction::handleProcNameWithVarSynonymOrWildcard() {
  string firstArgProcName = this->firstArgValue;
  string secondArgVarValue = this->secondArgValue;
  vector<string> modifiedVariables =
      pkb.getVarsModifiedByProc(firstArgProcName);
  //! If second arg is "_", wildcard table is built instead.
  return IntermediateTableFactory::buildSingleColTable(secondArgVarValue,
                                                       modifiedVariables);
}
