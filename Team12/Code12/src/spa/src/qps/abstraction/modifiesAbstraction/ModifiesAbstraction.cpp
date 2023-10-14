#include <unordered_set>

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
  string firstArgSynonym = this->firstArgValue;
  bool isFirstArgProcedure =
      this->context.getTokenEntity(firstArgSynonym) == PROCEDURE_ENTITY;
  string secondArgVarName = this->secondArgValue;

  // Modifies(procSynonym, *) and Modifies(stmtSynonym, *) has different APIs
  // with different return types
  if (isFirstArgProcedure) {
    unordered_set<string> proceduresModifyingVar =
        pkb.getProceduresModifying(secondArgVarName);
    return IntermediateTableFactory::buildSingleColTable(
        firstArgSynonym, proceduresModifyingVar);
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    vector<string> statementsModifyingVar =
        pkb.getStatementsModifying(secondArgVarName, firstArgStmtType);
    return IntermediateTableFactory::buildSingleColTable(
        firstArgSynonym, statementsModifyingVar);
  }
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
  string firstArgSynonym = this->firstArgValue;
  bool isFirstArgProcedure =
      this->context.getTokenEntity(firstArgSynonym) == PROCEDURE_ENTITY;
  string secondArgVarSynonym = this->secondArgValue;

  // Modifies(procSynonym, *) and Modifies(stmtSynonym, *) has different APIs
  vector<pair<string, string>> result;
  if (isFirstArgProcedure) {
    result = pkb.getAllModifiedVariablesByProcs();
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    result = pkb.getAllModifiedVariables(firstArgStmtType);
  }

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      firstArgSynonym, secondArgVarSynonym, result);
}

IntermediateTable
ModifiesAbstraction::handleProcNameWithVarSynonymOrWildcard() {
  string firstArgProcName = this->firstArgValue;
  string secondArgVarValue = this->secondArgValue;
  unordered_set<string> modifiedVariables =
      pkb.getModifiedVariablesForProc(firstArgProcName);
  //! If second arg is "_", wildcard table is built instead.
  return IntermediateTableFactory::buildSingleColTable(secondArgVarValue,
                                                       modifiedVariables);
}
