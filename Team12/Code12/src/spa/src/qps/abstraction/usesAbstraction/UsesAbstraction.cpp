#include "UsesAbstraction.h"

/**
 * Uses abstraction:
 * firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * secondArg: Synonym OR Identifier OR Wildcard
 */

// Uses (StatementOrProcSynonym, VarSynonym)
IntermediateTable UsesAbstraction::evaluateSynonymSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Uses (StatementOrProcSynonym, VarIdentifier)
IntermediateTable UsesAbstraction::evaluateSynonymIdent() {
  string firstArgSynonym = this->firstArgValue;
  bool isFirstArgProcedure =
      this->context.getTokenEntity(firstArgSynonym) == PROCEDURE_ENTITY;
  string secondArgVarName = this->secondArgValue;

  vector<string> result;
  // Uses(procSynonym, *) and Uses(stmtSynonym, *) has different APIs
  if (isFirstArgProcedure) {
    result = pkb.getProcUsing(secondArgVarName);
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    result = pkb.getStatementsUsing(secondArgVarName, firstArgStmtType);
  }
  return IntermediateTableFactory::buildSingleColTable(firstArgSynonym, result);
}

// Uses (StatementOrProcSynonym, _)
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

// Uses (ProcName, VarSynonym)
IntermediateTable UsesAbstraction::evaluateIdentSynonym() {
  return handleProcNameWithVarSynonymOrWildcard();
}

// Uses (ProcName, VarName)
IntermediateTable UsesAbstraction::evaluateIdentIdent() {
  string firstArgProcName = this->firstArgValue;
  string secondArgVarName = this->secondArgValue;
  bool isProcUsingVar =
      pkb.isVariableUsedByProc(firstArgProcName, secondArgVarName);

  return isProcUsingVar
             ? IntermediateTableFactory::buildWildcardIntermediateTable()
             : IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Uses (ProcName, _)
IntermediateTable UsesAbstraction::evaluateIdentWildcard() {
  return handleProcNameWithVarSynonymOrWildcard();
}

IntermediateTable UsesAbstraction::handleSynonymOrWildcardArgs() {
  string firstArgSynonym = this->firstArgValue;
  bool isFirstArgProcedure =
      this->context.getTokenEntity(firstArgSynonym) == PROCEDURE_ENTITY;
  string secondArgVarSynonym = this->secondArgValue;

  // Uses(procSynonym, *) and Uses(stmtSynonym, *) has different APIs
  vector<pair<string, string>> result;
  if (isFirstArgProcedure) {
    result = pkb.getUsesProcPairs();
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    result = pkb.getUsesStmtPairs(firstArgStmtType);
  }

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      firstArgSynonym, secondArgVarSynonym, result);
}

IntermediateTable UsesAbstraction::handleProcNameWithVarSynonymOrWildcard() {
  string firstArgProcName = this->firstArgValue;
  string secondArgVarValue = this->secondArgValue;
  vector<string> usedVariables = pkb.getVarsUsedByProc(firstArgProcName);
  //! If second arg is "_", wildcard table is built instead.
  return IntermediateTableFactory::buildSingleColTable(secondArgVarValue,
                                                       usedVariables);
}
