#include "UsesAbstraction.h"

#include <unordered_set>

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
  bool isFirstArgProcedure = firstArg.isProcSynonym();
  string secondArgVarName = this->secondArgValue;

  vector<string> result;
  // Uses(procSynonym, *) and Uses(stmtSynonym, *) has different APIs
  if (isFirstArgProcedure) {
    result = pkb.getProcUsing(secondArgVarName);
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    result = pkb.getStatementsUsing(secondArgVarName, firstArgStmtType);
  }
  return IntermediateTableFactory::buildSingleColTable(this->firstArgValue, result);
}

// Uses (StatementOrProcSynonym, _)
IntermediateTable UsesAbstraction::evaluateSynonymWildcard() {
  return handleSynonymOrWildcardArgs();
}

// Uses (StatementNumber, VarSynonym)
IntermediateTable UsesAbstraction::evaluateIntegerSynonym() {
  int firstArgStmtNumber = stoi(this->firstArgValue);
  string secondArgVarSynonym = this->secondArgValue;

  vector<pair<string, string>> result =
      pkb.getVariablesUsedBy(firstArgStmtNumber, StmtType::STMT);

  return IntermediateTableFactory::buildIntermediateTable(
      WILDCARD_KEYWORD, secondArgVarSynonym, result);
}

// Uses (StatementNumber, VarIdentifier)
IntermediateTable UsesAbstraction::evaluateIntegerIdent() {
  string firstArgStmtNumber = this->firstArgValue;
  string secondArgIdent = this->secondArgValue;

  if (pkb.isVariableUsedBy(secondArgIdent, firstArgStmtNumber)) {
    return IntermediateTableFactory::buildWildcardIntermediateTable();
  }
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Uses (StatementNumber, _)
IntermediateTable UsesAbstraction::evaluateIntegerWildcard() {
  int firstArgStmtNumber = stoi(this->firstArgValue);

  vector<pair<string, string>> result =
      pkb.getVariablesUsedBy(firstArgStmtNumber, StmtType::STMT);

  return IntermediateTableFactory::buildIntermediateTable(
      WILDCARD_KEYWORD, WILDCARD_KEYWORD, result);
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
  bool isFirstArgProcedure = firstArg.isProcSynonym();
  string secondArgVarSynonym = this->secondArgValue;

  // Uses(procSynonym, *) and Uses(stmtSynonym, *) has different APIs
  vector<pair<string, string>> result;
  if (isFirstArgProcedure) {
    result = pkb.getUsesProcPairs();
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    result = pkb.getAllUsedVariables(firstArgStmtType);
  }

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      this->firstArgValue, secondArgVarSynonym, result);
}

IntermediateTable UsesAbstraction::handleProcNameWithVarSynonymOrWildcard() {
  string firstArgProcName = this->firstArgValue;
  string secondArgVarValue = this->secondArgValue;
  vector<string> usedVariables = pkb.getVarsUsedByProc(firstArgProcName);
  //! If second arg is "_", wildcard table is built instead.
  return IntermediateTableFactory::buildSingleColTable(secondArgVarValue,
                                                       usedVariables);
}
