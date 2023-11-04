#include "WithEvaluator.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateStmtEntity() {
  vector<string> stmtsOfStmtType = pkbReader.getAllStmtsOf(StmtType::STMT);

  // build stmt synonymRes
  vector<std::reference_wrapper<SynonymRes>> stmtSynonymResObjs =
      buildStmtSynonymResVector(stmtsOfStmtType);

  return stmtSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::evaluateAssignEntity() {
  vector<string> stmtsOfAssignType = pkbReader.getAllStmtsOf(StmtType::ASSIGN);

  // build stmt synonymRes
  vector<std::reference_wrapper<SynonymRes>> assignSynonymResObjs =
      buildStmtSynonymResVector(stmtsOfAssignType);

  return assignSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateIfEntity() {
  vector<string> stmtsOfIfType = pkbReader.getAllStmtsOf(StmtType::IF);

  // build stmt synonymRes
  vector<std::reference_wrapper<SynonymRes>> ifSynonymResObjs =
      buildStmtSynonymResVector(stmtsOfIfType);

  return ifSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::evaluateWhileEntity() {
  vector<string> stmtsOfWhileType = pkbReader.getAllStmtsOf(StmtType::WHILE);

  // build stmt synonymRes
  vector<std::reference_wrapper<SynonymRes>> whileSynonymResObjs =
      buildStmtSynonymResVector(stmtsOfWhileType);

  return whileSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::evaluateConstantEntity() {
  vector<string> allConstants = pkbReader.getAllConstants();

  vector<std::reference_wrapper<SynonymRes>> constSynonymResObjs =
      buildConstantSynonymResVector(allConstants);

  return constSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateProcEntity() {
  vector<string> allProcs = pkbReader.getAllProcedures();

  vector<std::reference_wrapper<SynonymRes>> procSynonymResObjs =
      buildProcSynonymResVector(allProcs);

  return procSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateVarEntity() {
  vector<string> allVars = pkbReader.getAllVariables();

  vector<std::reference_wrapper<SynonymRes>> procSynonymResObjs =
      buildVarSynonymResVector(allVars);

  return procSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateCallEntity() {
  vector<pair<string, string>> allCallProcNamePairs =
      pkbReader.getAllStmtProcCallsPairs();

  vector<std::reference_wrapper<SynonymRes>> callSynonymResObjs =
      buildCallSynonymResVector(allCallProcNamePairs);

  return callSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateReadEntity() {
  vector<pair<string, string>> allReadVarNamePairs =
      pkbReader.getAllStmtVarReadPairs();

  vector<std::reference_wrapper<SynonymRes>> readSynonymResObjs =
      buildReadSynonymResVector(allReadVarNamePairs);

  return readSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::evaluatePrintEntity() {
  vector<pair<string, string>> allPrintVarNamePairs =
      pkbReader.getAllStmtVarPrintPairs();

  vector<std::reference_wrapper<SynonymRes>> printSynonymResObjs =
      buildPrintSynonymResVector(allPrintVarNamePairs);

  return printSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::buildStmtSynonymResVector(const vector<string>& stmtNums) {
  vector<std::reference_wrapper<SynonymRes>> stmtSynonymResObjs;
  stmtSynonymResObjs.reserve(stmtNums.size());
  for (const string& stmtNum : stmtNums) {
    stmtSynonymResObjs.emplace_back(
        SynonymResFactory::buildStmtSynonym(stmtNum));
  }

  return stmtSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::buildConstantSynonymResVector(
    const vector<string>& constantVals) {
  vector<std::reference_wrapper<SynonymRes>> constSynonymResObjs;
  constSynonymResObjs.reserve(constantVals.size());
  for (const string& constantVal : constantVals) {
    constSynonymResObjs.emplace_back(
        SynonymResFactory::buildConstantSynonym(constantVal));
  }

  return constSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::buildProcSynonymResVector(const vector<string>& procNames) {
  vector<std::reference_wrapper<SynonymRes>> procSynonymResObjs;
  procSynonymResObjs.reserve(procNames.size());
  for (const string& procName : procNames) {
    procSynonymResObjs.emplace_back(
        SynonymResFactory::buildProcSynonym(procName));
  }

  return procSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::buildVarSynonymResVector(const vector<string>& varNames) {
  vector<std::reference_wrapper<SynonymRes>> varSynonymResObjs;
  varSynonymResObjs.reserve(varNames.size());
  for (const string& varName : varNames) {
    varSynonymResObjs.emplace_back(SynonymResFactory::buildVarSynonym(varName));
  }

  return varSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::buildCallSynonymResVector(
    const vector<pair<string, string>>& callProcNamePairs) {
  vector<std::reference_wrapper<SynonymRes>> callSynonymResObjs;
  callSynonymResObjs.reserve(callProcNamePairs.size());
  for (const pair<string, string>& callProcNamePair : callProcNamePairs) {
    callSynonymResObjs.emplace_back(SynonymResFactory::buildCallsSynonym(
        callProcNamePair.first, callProcNamePair.second));
  }

  return callSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::buildReadSynonymResVector(
    const vector<pair<string, string>>& readVarNamePairs) {
  vector<std::reference_wrapper<SynonymRes>> readSynonymResObjs;

  readSynonymResObjs.reserve(readVarNamePairs.size());
  for (const auto& [firstVar, secondVar] : readVarNamePairs) {
    readSynonymResObjs.emplace_back(
        SynonymResFactory::buildReadSynonym(firstVar, secondVar));
  }

  return readSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::buildPrintSynonymResVector(
    const vector<pair<string, string>>& printVarNamePairs) {
  vector<std::reference_wrapper<SynonymRes>> printSynonymResObjs;

  printSynonymResObjs.reserve(printVarNamePairs.size());
  for (const auto& [firstVar, secondVar] : printVarNamePairs) {
    printSynonymResObjs.emplace_back(
        SynonymResFactory::buildReadSynonym(firstVar, secondVar));
  }

  return printSynonymResObjs;
}
