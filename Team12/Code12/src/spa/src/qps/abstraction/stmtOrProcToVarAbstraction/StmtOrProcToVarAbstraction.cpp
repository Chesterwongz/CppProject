#include "StmtOrProcToVarAbstraction.h"

#include <unordered_set>

/**
 * StmtOrProcToVarAbstraction abstraction:
 * - firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * - secondArg: Synonym OR Identifier OR Wildcard
 */

// Abstraction (StatementOrProcSynonym, VarSynonym)
IntermediateTable StmtOrProcToVarAbstraction::evaluateSynonymSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Abstraction (StatementOrProcSynonym, VarIdentifier)
IntermediateTable StmtOrProcToVarAbstraction::evaluateSynonymIdent() {
  string firstArgSynonym = this->firstArgValue;
  bool isFirstArgProcedure =
      this->context.getTokenEntity(firstArgSynonym) == PROCEDURE_ENTITY;
  string secondArgVarName = this->secondArgValue;

  vector<string> possibleValuesOfSynonym;
  // Abstraction(procSynonym, *) and Abstraction(stmtSynonym, *) has diff APIs
  if (isFirstArgProcedure) {
    possibleValuesOfSynonym = getProcsRelatedToVar(secondArgVarName);
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    possibleValuesOfSynonym =
        getStmtsRelatedToVar(secondArgVarName, firstArgStmtType);
  }
  return IntermediateTableFactory::buildSingleColTable(firstArgSynonym,
                                                       possibleValuesOfSynonym);
}

// Abstraction (StatementOrProcSynonym, _)
IntermediateTable StmtOrProcToVarAbstraction::evaluateSynonymWildcard() {
  return handleSynonymOrWildcardArgs();
}

// Abstraction (StatementNumber, VarSynonym)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIntegerSynonym() {
  int firstArgStmtNumber = stoi(this->firstArgValue);
  string secondArgVarSynonym = this->secondArgValue;

  vector<pair<string, string>> possibleStmtVarPairs =
      getVarsRelatedToStmt(firstArgStmtNumber, StmtType::STMT);

  return IntermediateTableFactory::buildIntermediateTable(
      WILDCARD_KEYWORD, secondArgVarSynonym, possibleStmtVarPairs);
}

// Abstraction (StatementNumber, VarIdentifier)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIntegerIdent() {
  string firstArgStmtNumber = this->firstArgValue;
  string secondArgIdent = this->secondArgValue;

  if (isVarRelatedToStmt(secondArgIdent, firstArgStmtNumber)) {
    return IntermediateTableFactory::buildWildcardIntermediateTable();
  }
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Abstraction (StatementNumber, _)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIntegerWildcard() {
  int firstArgStmtNumber = stoi(this->firstArgValue);

  vector<pair<string, string>> possibleStmtVarPairs =
      getVarsRelatedToStmt(firstArgStmtNumber, StmtType::STMT);

  return IntermediateTableFactory::buildIntermediateTable(
      WILDCARD_KEYWORD, WILDCARD_KEYWORD, possibleStmtVarPairs);
}

// Abstraction (ProcName, VarSynonym)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIdentSynonym() {
  return handleProcNameWithVarSynonymOrWildcard();
}

// Abstraction (ProcName, VarName)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIdentIdent() {
  string firstArgProcName = this->firstArgValue;
  string secondArgVarName = this->secondArgValue;
  bool isProcRelatedToVar =
      isVarRelatedToProc(secondArgVarName, firstArgProcName);

  return isProcRelatedToVar
             ? IntermediateTableFactory::buildWildcardIntermediateTable()
             : IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Abstraction (ProcName, _)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIdentWildcard() {
  return handleProcNameWithVarSynonymOrWildcard();
}

IntermediateTable StmtOrProcToVarAbstraction::handleSynonymOrWildcardArgs() {
  string firstArgSynonym = this->firstArgValue;
  bool isFirstArgProcedure =
      this->context.getTokenEntity(firstArgSynonym) == PROCEDURE_ENTITY;
  string secondArgVarSynonym = this->secondArgValue;

  // Abstraction(procSynonym, *) and Abstraction(stmtSynonym, *) has diff APIs
  vector<pair<string, string>> allStmtOrProcAndVarPairs;
  if (isFirstArgProcedure) {
    allStmtOrProcAndVarPairs = getAllProcVarRelations();
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    allStmtOrProcAndVarPairs = getAllStmtVarRelations(firstArgStmtType);
  }

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      firstArgSynonym, secondArgVarSynonym, allStmtOrProcAndVarPairs);
}

IntermediateTable
StmtOrProcToVarAbstraction::handleProcNameWithVarSynonymOrWildcard() {
  string firstArgProcName = this->firstArgValue;
  string secondArgVarValue = this->secondArgValue;
  vector<string> possibleVarValues = getVarsRelatedToProc(firstArgProcName);
  //! If second arg is "_", wildcard table is built instead.
  return IntermediateTableFactory::buildSingleColTable(secondArgVarValue,
                                                       possibleVarValues);
}
