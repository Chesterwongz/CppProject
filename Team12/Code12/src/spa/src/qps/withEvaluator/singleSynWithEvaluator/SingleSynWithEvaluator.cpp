#include "SingleSynWithEvaluator.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable SingleSynWithEvaluator::evaluate() {
  Entity synonymEntity = synonymArg.getEntityType();
  string synonymValue = synonymArg.getValue();

  vector<SynonymRes> synonymPKBResult = withEvaluatorFuncMap[synonymEntity]();
  IntermediateTable synonymResult =
      IntermediateTableFactory::buildSingleColTable(synonymValue,
                                                    synonymPKBResult);

  IntermediateTable valueArgResult = valueArgResultFuncMap[synonymEntity]();

  IntermediateTable finalResult = synonymResult.join(valueArgResult);

  return finalResult;
}

IntermediateTable SingleSynWithEvaluator::getCallValueArgResult() {
  string attrRefValue = valueArg.getValue();
  AttrRef attrRef = synonymArg.getAttrRef();
  string synonymValue = synonymArg.getValue();

  vector<SynonymRes> callSynonymResObjs;

  if (attrRef == ATTR_REF_STMT_NUMBER) {
    vector<string> procCalledBy =
        pkbReader.getProcCalledBy(std::stoi(attrRefValue));
    for (const string& procName : procCalledBy) {
      SynonymRes callSynonymRes =
          SynonymResFactory::buildCallsSynonym(attrRefValue, procName);
      callSynonymResObjs.push_back(callSynonymRes);
    }
  }

  if (attrRef == ATTR_REF_PROC_NAME) {
    vector<string> stmtsThatCall = pkbReader.getStmtsThatCall(attrRefValue);
    for (const string& stmtNum : stmtsThatCall) {
      SynonymRes callSynonymRes =
          SynonymResFactory::buildCallsSynonym(stmtNum, attrRefValue);
      callSynonymResObjs.push_back(callSynonymRes);
    }
  }

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, callSynonymResObjs);

  return result;
}

IntermediateTable SingleSynWithEvaluator::getReadValueArgResult() {
  string attrRefValue = valueArg.getValue();
  AttrRef attrRef = synonymArg.getAttrRef();
  string synonymValue = synonymArg.getValue();

  vector<SynonymRes> readSynonymResObjs;

  if (attrRef == ATTR_REF_STMT_NUMBER) {
    vector<string> varReadBy =
        pkbReader.getVariableReadBy(std::stoi(attrRefValue));
    for (const string& varName : varReadBy) {
      SynonymRes readSynonymRes =
          SynonymResFactory::buildReadSynonym(attrRefValue, varName);
      readSynonymResObjs.push_back(readSynonymRes);
    }
  }

  if (attrRef == ATTR_REF_VAR_NAME) {
    vector<string> stmtsThatRead = pkbReader.getStmtsThatRead(attrRefValue);
    for (const string& stmtNum : stmtsThatRead) {
      SynonymRes readSynonymRes =
          SynonymResFactory::buildReadSynonym(stmtNum, attrRefValue);
      readSynonymResObjs.push_back(readSynonymRes);
    }
  }

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, readSynonymResObjs);

  return result;
}

IntermediateTable SingleSynWithEvaluator::getPrintValueArgResult() {
  string attrRefValue = valueArg.getValue();
  AttrRef attrRef = synonymArg.getAttrRef();
  string synonymValue = synonymArg.getValue();

  vector<SynonymRes> printSynonymResObjs;

  if (attrRef == ATTR_REF_STMT_NUMBER) {
    vector<string> varPrintedBy =
        pkbReader.getVariablePrintedBy(std::stoi(attrRefValue));
    for (const string& varName : varPrintedBy) {
      SynonymRes printSynonymRes =
          SynonymResFactory::buildPrintSynonym(attrRefValue, varName);
      printSynonymResObjs.push_back(printSynonymRes);
    }
  }

  if (attrRef == ATTR_REF_VAR_NAME) {
    vector<string> stmtsThatPrint = pkbReader.getStmtsThatPrint(attrRefValue);
    for (const string& stmtNum : stmtsThatPrint) {
      SynonymRes printSynonymRes =
          SynonymResFactory::buildPrintSynonym(stmtNum, attrRefValue);
      printSynonymResObjs.push_back(printSynonymRes);
    }
  }

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, printSynonymResObjs);

  return result;
}

IntermediateTable SingleSynWithEvaluator::getStmtValueArgResult() {
  string attrRefValue = valueArg.getValue();
  string synonymValue = synonymArg.getValue();

  vector<SynonymRes> stmtSynonymResObjs;

  stmtSynonymResObjs.push_back(
      SynonymResFactory::buildStmtSynonym(attrRefValue));

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, stmtSynonymResObjs);

  return result;
}

IntermediateTable SingleSynWithEvaluator::getVarValueArgResult() {
  string attrRefValue = valueArg.getValue();
  string synonymValue = synonymArg.getValue();

  vector<SynonymRes> varSynonymResObjs;

  varSynonymResObjs.push_back(SynonymResFactory::buildVarSynonym(attrRefValue));

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, varSynonymResObjs);

  return result;
}

IntermediateTable SingleSynWithEvaluator::getConstantValueArgResult() {
  string attrRefValue = valueArg.getValue();
  string synonymValue = synonymArg.getValue();

  vector<SynonymRes> constSynonymResObjs;

  constSynonymResObjs.push_back(
      SynonymResFactory::buildConstantSynonym(attrRefValue));

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, constSynonymResObjs);

  return result;
}

IntermediateTable SingleSynWithEvaluator::getProcValueArgResult() {
  string attrRefValue = valueArg.getValue();
  string synonymValue = synonymArg.getValue();

  vector<SynonymRes> procSynonymResObjs;

  procSynonymResObjs.push_back(
      SynonymResFactory::buildProcSynonym(attrRefValue));

  IntermediateTable result = IntermediateTableFactory::buildSingleColTable(
      synonymValue, procSynonymResObjs);

  return result;
}
