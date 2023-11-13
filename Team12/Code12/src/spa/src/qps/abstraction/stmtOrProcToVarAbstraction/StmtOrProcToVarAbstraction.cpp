#include "StmtOrProcToVarAbstraction.h"

#include <unordered_set>

#include "qps/clause/utils/ClauseUtil.h"
#include "qps/clause/utils/SynResConversionUtils.h"

/**
 * StmtOrProcToVarAbstraction abstraction:
 * - firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * - secondArg: Synonym OR Identifier OR Wildcard
 */

bool StmtOrProcToVarAbstraction::isFirstSynonymInvalid() {
  bool isNotStmtOrProc =
      !(this->firstArg.isStmtSynonym() || this->firstArg.isProcSynonym());
  return isNotStmtOrProc;
}

bool StmtOrProcToVarAbstraction::isSecondSynonymInvalid() {
  bool isNotVarOrWildcard =
      !(this->secondArg.isVarSynonym() || this->secondArg.isWildcard());
  return isNotVarOrWildcard;
}

// Abstraction (StatementOrProcSynonym, VarSynonym)
IntermediateTable StmtOrProcToVarAbstraction::evaluateSynonymSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Abstraction (StatementOrProcSynonym, VarIdentifier)
IntermediateTable StmtOrProcToVarAbstraction::evaluateSynonymIdent() {
  return handleSecondArgVarIdent(secondArgValue);
}

IntermediateTable StmtOrProcToVarAbstraction::handleSecondArgVarIdent(
    const std::string& secondVarName) {
  if (isFirstSynonymInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  const string& firstArgSynonym = this->firstArgValue;
  bool isFirstArgProcedure = this->firstArg.isProcSynonym();

  vector<string> possibleValuesOfSynonym;
  // Abstraction(procSynonym, *) and Abstraction(stmtSynonym, *) has diff APIs
  if (isFirstArgProcedure) {
    possibleValuesOfSynonym = getProcsRelatedToVar(secondVarName);
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    possibleValuesOfSynonym =
        getStmtsRelatedToVar(secondVarName, firstArgStmtType);
  }

  vector<std::reference_wrapper<SynonymRes>> resultAsSynonymRes;
  if (SynResConversionUtils::isSingleColSynResCacheHit(this->signature)) {
    resultAsSynonymRes =
        SynResConversionUtils::getFromSingleColSynResCache(this->signature);
  } else {
    resultAsSynonymRes = SynResConversionUtils::toSynonymRes(
        possibleValuesOfSynonym, ClauseUtil::getArgEntity(this->firstArg),
        this->pkb);
    SynResConversionUtils::saveToSingleColSynResCache(this->signature,
                                                      resultAsSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(
      firstArgSynonym, std::move(resultAsSynonymRes));
}

// Abstraction (StatementOrProcSynonym, _)
IntermediateTable StmtOrProcToVarAbstraction::evaluateSynonymWildcard() {
  return handleSecondArgVarIdent(common::WILDCARD_VAR);
}

// Abstraction (StatementNumber, VarSynonym)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIntegerSynonym() {
  if (isSecondSynonymInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  int firstArgStmtNumber = stoi(this->firstArgValue);
  const string& secondArgVarSynonym = this->secondArgValue;

  vector<string> possibleVars = getVarsRelatedToStmt(firstArgStmtNumber);

  vector<std::reference_wrapper<SynonymRes>> resultAsSynonymRes;
  if (SynResConversionUtils::isSingleColSynResCacheHit(this->signature)) {
    resultAsSynonymRes =
        SynResConversionUtils::getFromSingleColSynResCache(this->signature);
  } else {
    resultAsSynonymRes = SynResConversionUtils::toSynonymRes(
        possibleVars, VARIABLE_ENTITY, this->pkb);
    SynResConversionUtils::saveToSingleColSynResCache(this->signature,
                                                      resultAsSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(
      secondArgVarSynonym, std::move(resultAsSynonymRes));
}

// Abstraction (StatementNumber, VarIdentifier)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIntegerIdent() {
  int firstArgStmtNumber = std::stoi(this->firstArgValue);
  string secondArgIdent = this->secondArgValue;

  if (isVarRelatedToStmt(firstArgStmtNumber, secondArgIdent)) {
    return IntermediateTableFactory::buildWildcardIntermediateTable();
  }
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// Abstraction (StatementNumber, _)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIntegerWildcard() {
  int firstArgStmtNumber = stoi(this->firstArgValue);

  vector<string> possibleVars = getVarsRelatedToStmt(firstArgStmtNumber);
  if (possibleVars.empty()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  return IntermediateTableFactory::buildWildcardIntermediateTable();
}

// Abstraction (ProcName, VarSynonym)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIdentSynonym() {
  return handleProcNameWithVarSynonymOrWildcard();
}

// Abstraction (ProcName, VarName)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIdentIdent() {
  //  string firstArgProcName = this->firstArgValue;
  //  string secondArgVarName = this->secondArgValue;
  //  bool isProcRelatedToVar =
  //      isVarRelatedToProc(firstArgProcName, secondArgVarName);
  //
  //  return isProcRelatedToVar
  //             ? IntermediateTableFactory::buildWildcardIntermediateTable()
  //             : IntermediateTableFactory::buildEmptyIntermediateTable();
  return handleProcNameVarName(firstArgValue, secondArgValue);
}

// Abstraction (ProcName, _)
IntermediateTable StmtOrProcToVarAbstraction::evaluateIdentWildcard() {
  //  return handleProcNameWithVarSynonymOrWildcard();
  return handleProcNameVarName(firstArgValue, common::WILDCARD_VAR);
}

IntermediateTable StmtOrProcToVarAbstraction::handleProcNameVarName(
    const string& procName, const string& varName) {
  bool isProcRelatedToVar = isVarRelatedToProc(procName, varName);
  return isProcRelatedToVar
             ? IntermediateTableFactory::buildWildcardIntermediateTable()
             : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable StmtOrProcToVarAbstraction::handleSynonymOrWildcardArgs() {
  if (isFirstSynonymInvalid() || isSecondSynonymInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  string firstArgSynonym = this->firstArgValue;
  bool isFirstArgProcedure = this->firstArg.isProcSynonym();
  string secondArgVarSynonym = this->secondArgValue;

  // Abstraction(procSynonym, *) and Abstraction(stmtSynonym, *) has diff APIs
  vector<pair<string, string>> allStmtOrProcAndVarPairs;
  if (isFirstArgProcedure) {
    allStmtOrProcAndVarPairs = getAllProcVarRelations();
  } else {
    StmtType firstArgStmtType = getFirstArgStmtType();
    allStmtOrProcAndVarPairs = getAllStmtVarRelations(firstArgStmtType);
  }

  pair<Entity, Entity> entityPair = {ClauseUtil::getArgEntity(this->firstArg),
                                     ClauseUtil::getArgEntity(this->secondArg)};
  vector<string> colNames = {firstArgSynonym, secondArgVarSynonym};
  TableDataType resultAsSynonymRes;
  if (SynResConversionUtils::isSynResCacheHit(this->signature)) {
    resultAsSynonymRes =
        SynResConversionUtils::getFromSynResCache(this->signature);
  } else {
    resultAsSynonymRes = SynResConversionUtils::toSynonymRes(
        allStmtOrProcAndVarPairs, entityPair, this->pkb);
    SynResConversionUtils::saveToSynResCache(this->signature,
                                             resultAsSynonymRes);
  }

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      colNames, std::move(resultAsSynonymRes));
}

IntermediateTable
StmtOrProcToVarAbstraction::handleProcNameWithVarSynonymOrWildcard() {
  if (isSecondSynonymInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  string firstArgProcName = this->firstArgValue;
  string secondArgVarValue = this->secondArgValue;
  vector<string> possibleVarValues = getVarsRelatedToProc(firstArgProcName);
  vector<std::reference_wrapper<SynonymRes>> resultAsSynonymRes;
  if (SynResConversionUtils::isSingleColSynResCacheHit(this->signature)) {
    resultAsSynonymRes =
        SynResConversionUtils::getFromSingleColSynResCache(this->signature);
  } else {
    resultAsSynonymRes = SynResConversionUtils::toSynonymRes(
        possibleVarValues, VARIABLE_ENTITY, this->pkb);
    SynResConversionUtils::saveToSingleColSynResCache(this->signature,
                                                      resultAsSynonymRes);
  }

  //! If second arg is "_", wildcard table is built instead.
  return IntermediateTableFactory::buildSingleColTable(
      secondArgVarValue, std::move(resultAsSynonymRes));
}
