#include "WithEvaluator.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/synonymRes/SynonymResFactory.h"

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateStmtEntity() {
  vector<string> stmtsOfStmtType = pkbReader.getAllStmtsOf(StmtType::STMT);

  // build stmt synonymRes
  vector<std::reference_wrapper<SynonymRes>> stmtSynonymResObjs =
      SynonymResFactory::buildStmtSynonymResVector(stmtsOfStmtType);

  return stmtSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::evaluateAssignEntity() {
  vector<string> stmtsOfAssignType = pkbReader.getAllStmtsOf(StmtType::ASSIGN);

  // build stmt synonymRes
  vector<std::reference_wrapper<SynonymRes>> assignSynonymResObjs =
      SynonymResFactory::buildStmtSynonymResVector(stmtsOfAssignType);

  return assignSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateIfEntity() {
  vector<string> stmtsOfIfType = pkbReader.getAllStmtsOf(StmtType::IF);

  // build stmt synonymRes
  vector<std::reference_wrapper<SynonymRes>> ifSynonymResObjs =
      SynonymResFactory::buildStmtSynonymResVector(stmtsOfIfType);

  return ifSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::evaluateWhileEntity() {
  vector<string> stmtsOfWhileType = pkbReader.getAllStmtsOf(StmtType::WHILE);

  // build stmt synonymRes
  vector<std::reference_wrapper<SynonymRes>> whileSynonymResObjs =
      SynonymResFactory::buildStmtSynonymResVector(stmtsOfWhileType);

  return whileSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::evaluateConstantEntity() {
  vector<string> allConstants = pkbReader.getAllConstants();

  vector<std::reference_wrapper<SynonymRes>> constSynonymResObjs =
      SynonymResFactory::buildConstantSynonymResVector(allConstants);

  return constSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateProcEntity() {
  vector<string> allProcs = pkbReader.getAllProcedures();

  vector<std::reference_wrapper<SynonymRes>> procSynonymResObjs =
      SynonymResFactory::buildProcSynonymResVector(allProcs);

  return procSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateVarEntity() {
  vector<string> allVars = pkbReader.getAllVariables();

  vector<std::reference_wrapper<SynonymRes>> procSynonymResObjs =
      SynonymResFactory::buildVarSynonymResVector(allVars);

  return procSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateCallEntity() {
  vector<pair<string, string>> allCallProcNamePairs =
      pkbReader.getAllStmtProcCallsPairs();

  vector<std::reference_wrapper<SynonymRes>> callSynonymResObjs =
      SynonymResFactory::buildCallSynonymResVector(allCallProcNamePairs);

  return callSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>> WithEvaluator::evaluateReadEntity() {
  vector<pair<string, string>> allReadVarNamePairs =
      pkbReader.getAllStmtVarReadPairs();

  vector<std::reference_wrapper<SynonymRes>> readSynonymResObjs =
      SynonymResFactory::buildReadSynonymResVector(allReadVarNamePairs);

  return readSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
WithEvaluator::evaluatePrintEntity() {
  vector<pair<string, string>> allPrintVarNamePairs =
      pkbReader.getAllStmtVarPrintPairs();

  vector<std::reference_wrapper<SynonymRes>> printSynonymResObjs =
      SynonymResFactory::buildPrintSynonymResVector(allPrintVarNamePairs);

  return printSynonymResObjs;
}
