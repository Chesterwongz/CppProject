#include "SingleSynWithEvaluator.h"

#include <vector>

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable SingleSynWithEvaluator::evaluate() {
  Entity synonymEntity = synonymArg.getEntityType();
  string synonymValue = synonymArg.getValue();

  vector<std::reference_wrapper<SynonymRes>> synonymPKBResult =
      singleSynWithEvaluatorFuncMap[synonymEntity]();
  IntermediateTable synonymResult =
      IntermediateTableFactory::buildSingleColTable(synonymValue,
                                                    synonymPKBResult);

  return synonymResult;
}

vector<std::reference_wrapper<SynonymRes>>
SingleSynWithEvaluator::evaluateStmtTypes(StmtType stmtType) {
  string attrRefValue = valueArg.getValue();
  AttrRef attrRef = synonymArg.getAttrRef();
  string synonymValue = synonymArg.getValue();

  vector<string> stmtsOfStmtType = pkbReader.getAllStmtsOf(stmtType);
  vector<string> filtered;

  std::copy_if(std::begin(stmtsOfStmtType), std::end(stmtsOfStmtType),
               std::back_inserter(filtered),
               [&attrRefValue](const string& stmtNo) -> bool {
                 return stmtNo == attrRefValue;
               });

  // build stmt synonymRes
  vector<std::reference_wrapper<SynonymRes>> stmtSynonymResObjs =
      SynonymResFactory::buildStmtSynonymResVector(filtered);

  return stmtSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
SingleSynWithEvaluator::evaluateStmtEntity() {
  return std::move(evaluateStmtTypes(StmtType::STMT));
}

vector<std::reference_wrapper<SynonymRes>>
SingleSynWithEvaluator::evaluateAssignEntity() {
  return std::move(evaluateStmtTypes(StmtType::ASSIGN));
}

vector<std::reference_wrapper<SynonymRes>>
SingleSynWithEvaluator::evaluateIfEntity() {
  return std::move(evaluateStmtTypes(StmtType::IF));
}

vector<std::reference_wrapper<SynonymRes>>
SingleSynWithEvaluator::evaluateWhileEntity() {
  return std::move(evaluateStmtTypes(StmtType::WHILE));
}

vector<std::reference_wrapper<SynonymRes>>
SingleSynWithEvaluator::evaluateConstantEntity() {
  string attrRefValue = valueArg.getValue();
  string synonymValue = synonymArg.getValue();

  bool doesConstExists = pkbReader.isValidConstant(attrRefValue);

  vector<std::reference_wrapper<SynonymRes>> constSynonymResObject = {};
  if (doesConstExists) {
    constSynonymResObject.emplace_back(
        SynonymResFactory::buildConstantSynonym(attrRefValue));
  }

  return constSynonymResObject;
}

vector<std::reference_wrapper<SynonymRes>>
SingleSynWithEvaluator::evaluateProcEntity() {
  string attrRefValue = valueArg.getValue();
  AttrRef attrRef = synonymArg.getAttrRef();
  string synonymValue = synonymArg.getValue();

  bool doesProcExists = pkbReader.isValidProc(attrRefValue);
  vector<std::reference_wrapper<SynonymRes>> procSynonymResObjs = {};
  if (doesProcExists) {
    procSynonymResObjs.emplace_back(
        SynonymResFactory::buildProcSynonym(attrRefValue));
  }

  return procSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
SingleSynWithEvaluator::evaluateVarEntity() {
  string attrRefValue = valueArg.getValue();
  AttrRef attrRef = synonymArg.getAttrRef();
  string synonymValue = synonymArg.getValue();

  bool doesVarExists = pkbReader.isValidVariable(attrRefValue);
  vector<std::reference_wrapper<SynonymRes>> varSynonymResObjs = {};

  if (doesVarExists) {
    varSynonymResObjs.emplace_back(
        SynonymResFactory::buildVarSynonym(attrRefValue));
  }

  return varSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
SingleSynWithEvaluator::evaluateCallEntity() {
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

  return callSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
SingleSynWithEvaluator::evaluateReadEntity() {
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

  return readSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
SingleSynWithEvaluator::evaluatePrintEntity() {
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

  return printSynonymResObjs;
}
