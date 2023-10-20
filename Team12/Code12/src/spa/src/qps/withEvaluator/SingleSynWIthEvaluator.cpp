#include "qps/withEvaluator/SingleSynWithEvaluator.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable SingleSynWithEvaluator::evaluate(PKBReader& pkbReader) {
  Entity_AttrRef_Permutation permutation =
      getPermutation(synonymArg->getEntityType(), synonymArg->getAttrRef());

  IntermediateTable pkbResult = withEvaluatorFuncMap[permutation](pkbReader);

  return pkbResult;
}

IntermediateTable SingleSynWithEvaluator::evaluateStmtNum(
    PKBReader& pkbReader) {
  string synonymArgValue = synonymArg->getValue();
  Entity synonymEntity = synonymArg->getEntityType();
  string attrRefValue = valueArg->getValue();

  StmtType stmtType = StmtEntityToStatementType.at(synonymEntity);
  bool isValidStmt = pkbReader.isValidStmt(std::stoi(attrRefValue), stmtType);

  if (!isValidStmt) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};
  return IntermediateTableFactory::buildSingleColTable(synonymArgValue, result);
}

IntermediateTable SingleSynWithEvaluator::evaluateConstantValue(
    PKBReader& pkbReader) {
  string synonymArgValue = synonymArg->getValue();
  string attrRefValue = valueArg->getValue();

  bool isValidConstant = pkbReader.isValidConstant(attrRefValue);

  if (!isValidConstant) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};

  return IntermediateTableFactory::buildSingleColTable(synonymArgValue, result);
}

IntermediateTable SingleSynWithEvaluator::evaluateProcName(
    PKBReader& pkbReader) {
  string synonymArgValue = synonymArg->getValue();
  string attrRefValue = valueArg->getValue();

  bool isValidProcName = pkbReader.isValidProc(attrRefValue);

  if (!isValidProcName) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};

  return IntermediateTableFactory::buildSingleColTable(synonymArgValue, result);
}

IntermediateTable SingleSynWithEvaluator::evaluateVarName(
    PKBReader& pkbReader) {
  string synonymArgValue = synonymArg->getValue();
  string attrRefValue = valueArg->getValue();

  bool isValidVariable = pkbReader.isValidVariable(attrRefValue);

  if (!isValidVariable) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};

  return IntermediateTableFactory::buildSingleColTable(synonymArgValue, result);
}

// for call.procname
IntermediateTable SingleSynWithEvaluator::evaluateCallProcName(
    PKBReader& pkbReader) {
  string synonymArgValue = synonymArg->getValue();
  string attrRefValue = valueArg->getValue();

  vector<string> stmtsThatCallProcName =
      pkbReader.getStmtsThatCall(attrRefValue);

  if (stmtsThatCallProcName.size() == 0) {
    // c.procName = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<SynonymRes> callsSynonymResColData;

  // create call synonymRes objs
  for (string stmtNum : stmtsThatCallProcName) {
    SynonymRes callsSynonymRes =
        SynonymResFactory::buildCallsSynonym(stmtNum, attrRefValue);

    callsSynonymResColData.push_back(callsSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(synonymArgValue,
                                                       callsSynonymResColData);
}

// for call.stmtNum
IntermediateTable SingleSynWithEvaluator::evaluateCallStmtNum(
    PKBReader& pkbReader) {
  string synonymArgValue = synonymArg->getValue();
  string attrRefValue = valueArg->getValue();

  vector<string> procNameCalledByStmtNum =
      pkbReader.getProcCalledBy(std::stoi(attrRefValue));

  if (procNameCalledByStmtNum.size() == 0) {
    // c.stmtNum = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<SynonymRes> callsSynonymResColData;

  // create call synonymRes objs
  for (string procName : procNameCalledByStmtNum) {
    SynonymRes callsSynonymRes =
        SynonymResFactory::buildCallsSynonym(attrRefValue, procName);

    callsSynonymResColData.push_back(callsSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(synonymArgValue,
                                                       callsSynonymResColData);
}

// for read.varName
IntermediateTable SingleSynWithEvaluator::evaluateReadVarName(
    PKBReader& pkbReader) {
  string synonymArgValue = synonymArg->getValue();
  string attrRefValue = valueArg->getValue();

  vector<string> stmtsThatReadVarName =
      pkbReader.getStmtsThatRead(attrRefValue);

  if (stmtsThatReadVarName.size() == 0) {
    // r.varName = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<SynonymRes> readSynonymResColData;

  // create read synonymRes objs
  for (string stmtNum : stmtsThatReadVarName) {
    SynonymRes readSynonymRes =
        SynonymResFactory::buildReadSynonym(stmtNum, attrRefValue);

    readSynonymResColData.push_back(readSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(synonymArgValue,
                                                       readSynonymResColData);
}

// for read.stmt#
IntermediateTable SingleSynWithEvaluator::evaluateReadStmtNum(
    PKBReader& pkbReader) {
  string synonymArgValue = synonymArg->getValue();
  string attrRefValue = valueArg->getValue();

  vector<string> varReadByStmtNum =
      pkbReader.getVariableReadBy(std::stoi(attrRefValue));

  if (varReadByStmtNum.empty()) {
    // r.stmt# = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<SynonymRes> readSynonymResColData;

  // create read synonymRes objs
  for (string varName : varReadByStmtNum) {
    SynonymRes readSynonymRes =
        SynonymResFactory::buildReadSynonym(attrRefValue, varName);

    readSynonymResColData.push_back(readSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(synonymArgValue,
                                                       readSynonymResColData);
}

// for print.varName
IntermediateTable SingleSynWithEvaluator::evaluatePrintVarName(
    PKBReader& pkbReader) {
  string synonymArgValue = synonymArg->getValue();
  string attrRefValue = valueArg->getValue();

  vector<string> stmtsThatPrintVarName =
      pkbReader.getStmtsThatPrint(attrRefValue);

  if (stmtsThatPrintVarName.size() == 0) {
    // print.varName = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<SynonymRes> printSynonymResColData;

  // create read synonymRes objs
  for (string stmtNum : stmtsThatPrintVarName) {
    SynonymRes printSynonymRes =
        SynonymResFactory::buildPrintSynonym(stmtNum, attrRefValue);

    printSynonymResColData.push_back(printSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(synonymArgValue,
                                                       printSynonymResColData);
}

// for print.stmt#
IntermediateTable SingleSynWithEvaluator::evaluatePrintStmtNum(
    PKBReader& pkbReader) {
  string synonymArgValue = synonymArg->getValue();
  string attrRefValue = valueArg->getValue();

  vector<string> varPrintedByStmtNum =
      pkbReader.getVariablePrintedBy(std::stoi(attrRefValue));

  if (varPrintedByStmtNum.size() == 0) {
    // print.stmt# = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<SynonymRes> printSynonymResColData;

  // create read synonymRes objs
  for (string varName : varPrintedByStmtNum) {
    SynonymRes printSynonymRes =
        SynonymResFactory::buildPrintSynonym(attrRefValue, varName);

    printSynonymResColData.push_back(printSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(synonymArgValue,
                                                       printSynonymResColData);
}
