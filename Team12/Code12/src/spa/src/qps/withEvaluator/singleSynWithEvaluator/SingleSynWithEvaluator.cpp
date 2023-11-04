#include "SingleSynWithEvaluator.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable SingleSynWithEvaluator::evaluate() {
  Entity synonymEntity = synonymArg.getEntityType();
  string synonymValue = synonymArg.getValue();

  vector<std::reference_wrapper<SynonymRes>> synonymPKBResult =
      withEvaluatorFuncMap[synonymEntity]();
  IntermediateTable synonymResult =
      IntermediateTableFactory::buildSingleColTable(
          synonymValue, std::move(synonymPKBResult));

  IntermediateTable valueArgResult = valueArgResultFuncMap[synonymEntity]();

  IntermediateTable finalResult = synonymResult.join(valueArgResult);

  return finalResult;
}

IntermediateTable SingleSynWithEvaluator::getCallValueArgResult() {
  string attrRefValue = valueArg.getValue();
  AttrRef attrRef = synonymArg.getAttrRef();
  string synonymValue = synonymArg.getValue();

  vector<std::reference_wrapper<SynonymRes>> callSynonymResObjs;

  if (attrRef == ATTR_REF_STMT_NUMBER) {
    vector<string> procCalledBy =
        pkbReader.getProcCalledBy(std::stoi(attrRefValue));
    for (const string& procName : procCalledBy) {
      callSynonymResObjs.emplace_back(
          SynonymResFactory::buildCallsSynonym(attrRefValue, procName));
    }
  }

  if (attrRef == ATTR_REF_PROC_NAME) {
    vector<string> stmtsThatCall = pkbReader.getStmtsThatCall(attrRefValue);
    for (const string& stmtNum : stmtsThatCall) {
      callSynonymResObjs.emplace_back(
          SynonymResFactory::buildCallsSynonym(stmtNum, attrRefValue));
    }
  }

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, std::move(callSynonymResObjs));

  return result;
}

IntermediateTable SingleSynWithEvaluator::getReadValueArgResult() {
  string attrRefValue = valueArg.getValue();
  AttrRef attrRef = synonymArg.getAttrRef();
  string synonymValue = synonymArg.getValue();

  vector<std::reference_wrapper<SynonymRes>> readSynonymResObjs;

  if (attrRef == ATTR_REF_STMT_NUMBER) {
    vector<string> varReadBy =
        pkbReader.getVariableReadBy(std::stoi(attrRefValue));
    for (const string& varName : varReadBy) {
      readSynonymResObjs.emplace_back(
          SynonymResFactory::buildReadSynonym(attrRefValue, varName));
    }
  }

  if (attrRef == ATTR_REF_VAR_NAME) {
    vector<string> stmtsThatRead = pkbReader.getStmtsThatRead(attrRefValue);
    for (const string& stmtNum : stmtsThatRead) {
      readSynonymResObjs.emplace_back(
          SynonymResFactory::buildReadSynonym(stmtNum, attrRefValue));
    }
  }

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, std::move(readSynonymResObjs));

  return result;
}

IntermediateTable SingleSynWithEvaluator::getPrintValueArgResult() {
  string attrRefValue = valueArg.getValue();
  AttrRef attrRef = synonymArg.getAttrRef();
  string synonymValue = synonymArg.getValue();

  vector<std::reference_wrapper<SynonymRes>> printSynonymResObjs;

  if (attrRef == ATTR_REF_STMT_NUMBER) {
    vector<string> varPrintedBy =
        pkbReader.getVariablePrintedBy(std::stoi(attrRefValue));
    for (const string& varName : varPrintedBy) {
      printSynonymResObjs.emplace_back(
          SynonymResFactory::buildPrintSynonym(attrRefValue, varName));
    }
  }

  if (attrRef == ATTR_REF_VAR_NAME) {
    vector<string> stmtsThatPrint = pkbReader.getStmtsThatPrint(attrRefValue);
    for (const string& stmtNum : stmtsThatPrint) {
      printSynonymResObjs.emplace_back(
          SynonymResFactory::buildPrintSynonym(stmtNum, attrRefValue));
    }
  }

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, std::move(printSynonymResObjs));

  return result;
}

IntermediateTable SingleSynWithEvaluator::getStmtValueArgResult() {
  string attrRefValue = valueArg.getValue();
  string synonymValue = synonymArg.getValue();

  vector<std::reference_wrapper<SynonymRes>> stmtSynonymResObjs = {
      SynonymResFactory::buildStmtSynonym(attrRefValue)};

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, std::move(stmtSynonymResObjs));

  return result;
}

IntermediateTable SingleSynWithEvaluator::getVarValueArgResult() {
  string attrRefValue = valueArg.getValue();
  string synonymValue = synonymArg.getValue();

  vector<std::reference_wrapper<SynonymRes>> varSynonymResObjs = {
      SynonymResFactory::buildVarSynonym(attrRefValue)};

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, std::move(varSynonymResObjs));

  return result;
}

IntermediateTable SingleSynWithEvaluator::getConstantValueArgResult() {
  string attrRefValue = valueArg.getValue();
  string synonymValue = synonymArg.getValue();

  vector<std::reference_wrapper<SynonymRes>> constSynonymResObjs = {
      SynonymResFactory::buildConstantSynonym(attrRefValue)};

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, std::move(constSynonymResObjs));

  return result;
}

IntermediateTable SingleSynWithEvaluator::getProcValueArgResult() {
  string attrRefValue = valueArg.getValue();
  string synonymValue = synonymArg.getValue();

  vector<std::reference_wrapper<SynonymRes>> procSynonymResObjs = {
      SynonymResFactory::buildProcSynonym(attrRefValue)};

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, std::move(procSynonymResObjs));

  return result;
}
