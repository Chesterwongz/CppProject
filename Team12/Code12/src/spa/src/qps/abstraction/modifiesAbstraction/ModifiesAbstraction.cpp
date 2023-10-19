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
  bool isFirstArgProcedure = firstArg.isProcSynonym();
  string secondArgVarName = this->secondArgValue;

  vector<string> result;
  // Modifies(procSynonym, *) and Modifies(stmtSynonym, *) has different APIs
  if (isFirstArgProcedure) {
    result = pkb.getProcModifying(secondArgVarName);
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    result = pkb.getStatementsModifying(secondArgVarName, firstArgStmtType);
  }
  return IntermediateTableFactory::buildSingleColTable(this->firstArgValue,
                                                       result);
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

IntermediateTable ModifiesAbstraction::handleSynonymOrWildcardArgs() {
  bool isFirstArgProcedure = firstArg.isProcSynonym();
  string secondArgVarSynonym = this->secondArgValue;

  // Modifies(procSynonym, *) and Modifies(stmtSynonym, *) has different APIs
  vector<pair<string, string>> result;
  if (isFirstArgProcedure) {
    result = pkb.getModifiesProcPairs();
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    result = pkb.getAllModifiedVariables(firstArgStmtType);
  }

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      this->firstArgValue, secondArgVarSynonym, result);
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
