#include <vector>
#include <string>

#include "WithEvaluator.h"
#include "qps/clause/utils/ClauseConstants.h"

vector<SynonymRes> WithEvaluator::evaluateStmtEntity() {
  vector<string> stmtsOfStmtType = pkbReader.getAllStmtsOf(StmtType::STMT);

  // build stmt synonymRes
  vector<SynonymRes> stmtSynonymResObjs =
      buildStmtSynonymResVector(stmtsOfStmtType);

  return stmtSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::evaluateAssignEntity() {

  vector<string> stmtsOfAssignType = pkbReader.getAllStmtsOf(StmtType::ASSIGN);

  // build stmt synonymRes
  vector<SynonymRes> assignSynonymResObjs =
      buildStmtSynonymResVector(stmtsOfAssignType);

  return assignSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::evaluateIfEntity() {
  vector<string> stmtsOfIfType = pkbReader.getAllStmtsOf(StmtType::IF);

  // build stmt synonymRes
  vector<SynonymRes> ifSynonymResObjs =
      buildStmtSynonymResVector(stmtsOfIfType);

  return ifSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::evaluateWhileEntity() {
  vector<string> stmtsOfWhileType = pkbReader.getAllStmtsOf(StmtType::WHILE);

  // build stmt synonymRes
  vector<SynonymRes> whileSynonymResObjs =
      buildStmtSynonymResVector(stmtsOfWhileType);

  return whileSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::evaluateConstantEntity() {
  vector<string> allConstants = pkbReader.getAllConstants();

  vector<SynonymRes> constSynonymResObjs =
      buildConstantSynonymResVector(allConstants);

  return constSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::evaluateProcEntity() {
  vector<string> allProcs = pkbReader.getAllProcedures();

  vector<SynonymRes> procSynonymResObjs = buildProcSynonymResVector(allProcs);

  return procSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::evaluateVarEntity() {
  vector<string> allVars = pkbReader.getAllVariables();

  vector<SynonymRes> procSynonymResObjs = buildVarSynonymResVector(allVars);

  return procSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::evaluateCallEntity() {
  vector<pair<string, string>> allCallProcNamePairs =
      pkbReader.getAllStmtProcCallsPairs();

  vector<SynonymRes> callSynonymResObjs =
      buildCallSynonymResVector(allCallProcNamePairs);

  return callSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::evaluateReadEntity() {
  vector<pair<string, string>> allReadVarNamePairs =
      pkbReader.getAllStmtVarReadPairs();

  vector<SynonymRes> readSynonymResObjs =
      buildReadSynonymResVector(allReadVarNamePairs);

  return readSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::evaluatePrintEntity() {
  
  vector<pair<string, string>> allPrintVarNamePairs =
      pkbReader.getAllStmtVarPrintPairs();

  vector<SynonymRes> printSynonymResObjs =
      buildPrintSynonymResVector(allPrintVarNamePairs);

  return printSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::buildStmtSynonymResVector(vector<string> stmtNums) {
  vector<SynonymRes> stmtSynonymResObjs;

  for (string stmtNum : stmtNums) {
    SynonymRes stmtSynonymRes = SynonymResFactory::buildStmtSynonym(stmtNum);

    stmtSynonymResObjs.push_back(stmtSynonymRes);
  }

  return stmtSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::buildConstantSynonymResVector(
    vector<string> constantVals) {
  vector<SynonymRes> constSynonymResObjs;

  for (string constantVal : constantVals) {
    SynonymRes constSynonymRes =
        SynonymResFactory::buildConstantSynonym(constantVal);

    constSynonymResObjs.push_back(constSynonymRes);
  }

  return constSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::buildProcSynonymResVector(
    vector<string> procNames) {
  vector<SynonymRes> procSynonymResObjs;

  for (string procName : procNames) {
    SynonymRes procSynonymRes =
        SynonymResFactory::buildProcSynonym(procName);

    procSynonymResObjs.push_back(procSynonymRes);
  }

  return procSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::buildVarSynonymResVector(
    vector<string> varNames) {
  vector<SynonymRes> varSynonymResObjs;

  for (string varName : varNames) {
    SynonymRes varSynonymRes = SynonymResFactory::buildVarSynonym(varName);

    varSynonymResObjs.push_back(varSynonymRes);
  }

  return varSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::buildCallSynonymResVector(
    vector<pair<string, string>> callProcNamePairs) {
  vector<SynonymRes> callSynonymResObjs;

  for (pair<string, string> callProcNamePair : callProcNamePairs) {
    SynonymRes callSynonymRes = SynonymResFactory::buildCallsSynonym(callProcNamePair.first, callProcNamePair.second);

    callSynonymResObjs.push_back(callSynonymRes);
  }

  return callSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::buildReadSynonymResVector(
    vector<pair<string, string>> readVarNamePairs) {
  vector<SynonymRes> readSynonymResObjs;

  for (pair<string, string> readVarNamePair : readVarNamePairs) {
    SynonymRes readSynonymRes = SynonymResFactory::buildReadSynonym(
        readVarNamePair.first, readVarNamePair.second);

    readSynonymResObjs.push_back(readSynonymRes);
  }

  return readSynonymResObjs;
}

vector<SynonymRes> WithEvaluator::buildPrintSynonymResVector(
    vector<pair<string, string>> printVarNamePairs) {
  vector<SynonymRes> printSynonymResObjs;

  for (pair<string, string> printVarNamePair : printVarNamePairs) {
    SynonymRes printSynonymRes = SynonymResFactory::buildReadSynonym(
        printVarNamePair.first, printVarNamePair.second);

    printSynonymResObjs.push_back(printSynonymRes);
  }

  return printSynonymResObjs;
}
