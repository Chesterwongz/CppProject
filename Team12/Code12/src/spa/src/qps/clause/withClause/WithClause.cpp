#include "qps/clause/withClause/WithClause.h"

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable WithClause::evaluate(Context& context, PKBReader& pkb) {
  IntermediateTable pkbResult =
      withEvaluatorFuncMap[permutation](pkb);

  return pkbResult;
  //return IntermediateTableFactory::buildEmptyIntermediateTable();
}

bool WithClause::isEquals(const Clause& other) { 
  const auto* otherClause = dynamic_cast<const WithClause*>(&other);
  if (!otherClause) return false;

  return *synonym == *(otherClause->synonym) &&
         attrRefValue == otherClause->attrRefValue;
}

IntermediateTable WithClause::evaluateStmtNum(PKBReader& pkbReader) {
  StmtType stmtType = StmtEntityToStatementType.at(synonymEntity);
  bool isValidStmt = pkbReader.isValidStmt(std::stoi(attrRefValue), stmtType);

  if (!isValidStmt) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};
  // TODO (houten) integrate with synonymres
  // return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                     result);
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable WithClause::evaluateConstantValue(PKBReader& pkbReader) {
  bool isValidConstant = pkbReader.isValidConstant(attrRefValue);

  if (!isValidConstant) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};
  // TODO (houten) integrate with synonymres
  /* return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
                                                       result);*/
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable WithClause::evaluateProcName(PKBReader& pkbReader) {
  bool isValidProcName = pkbReader.isValidProc(attrRefValue);

  if (!isValidProcName) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};

  // TODO (houten) integrate with synonymres
  // return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                     result);
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable WithClause::evaluateVarName(PKBReader& pkbReader) {
  bool isValidVariable = pkbReader.isValidVariable(attrRefValue);

  if (!isValidVariable) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};
  // TODO (houten) integrate with synonymres
  // return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                     result);
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// for call.procname
IntermediateTable WithClause::evaluateCallProcName(PKBReader& pkbReader) {
   vector<string> stmtsThatCallProcName =
       pkbReader.getStmtsThatCall(attrRefValue);

   if (stmtsThatCallProcName.size() == 0) {
     // c.procName = attrRefVal does not exist
     return IntermediateTableFactory::buildEmptyIntermediateTable();
   }
   // TODO: integrate with synonymRes
  // vector<SynonymRes> callsSynonymResColData;

  //// create call synonymRes objs
  // for (string stmtNum : stmtsThatCallProcName) {
  //
  //   SynonymRes callsSynonymRes =
  //   SynonymResFactory::buildCallsSynonym(stmtNum, attrRefValue);
  //   callsSynonymResColData.push_back(callsSynonymRes);
  // }

  // return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                      callsSynonymResColData);
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// for call.stmtNum
IntermediateTable WithClause::evaluateCallStmtNum(PKBReader& pkbReader) {
  vector<string> procNameCalledByStmtNum =
       pkbReader.getProcCalledBy(std::stoi(attrRefValue));

  if (procNameCalledByStmtNum.size() == 0) {
    // c.stmtNum = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  // TODO (houten) integrate with synonymRes

  //vector<SynonymRes> callsSynonymResColData;
  //
  //// create call synonymRes objs
  //for (int i = 0; i < procNameCalledByStmtNum.size(); i++) {
  //  SynonymRes callsSynonymRes = SynonymResFactory::buildCallsSynonym(
  //      attrRefValue, procNameCalledByStmtNum);
  //  callsSynonymResColData.push_back(callsSynonymRes);
  //}  
  //
  //return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                    callsSynonymResColData);
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// for read.varName
IntermediateTable WithClause::evaluateReadVarName(PKBReader& pkbReader) {
  vector<string> stmtsThatReadVarName =
      pkbReader.getStmtsThatRead(attrRefValue);

  if (stmtsThatReadVarName.size() == 0) {
    // r.varName = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  // TODO (houten) integrate with synonymRes

  //vector<SynonymRes> readSynonymResColData;
  //
  //// create read synonymRes objs
  //for (string stmtNum : stmtsThatReadVarName) {
  //  SynonymRes readSynonymRes =
  //      SynonymResFactory::buildReadSynonym(stmtNum, attrRefValue);
  //  readSynonymResColData.push_back(readSynonymRes);
  //}

  //return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                    readSynonymResColData);
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// for read.stmt#
IntermediateTable WithClause::evaluateReadStmtNum(PKBReader& pkbReader) {
  vector<string> varReadByStmtNum =
  pkbReader.getVariableReadBy(std::stoi(attrRefValue));

  if (varReadByStmtNum.empty()) {
    // r.stmt# = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  // TODO (houten) integrate with synonymRes
  //vector<SynonymRes> readSynonymResColData;

  //// create read synonymRes objs
  //for (int i = 0; i < varReadByStmtNum.size(); i++) {
  //  SynonymRes readSynonymRes =
  //      SynonymResFactory::buildReadSynonym(attrRefValue, varReadByStmtNum);
  //  readSynonymResColData.push_back(readSynonymRes);
  //}

  //return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                    readSynonymResColData);
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// for print.varName
IntermediateTable WithClause::evaluatePrintVarName(PKBReader& pkbReader) {
  vector<string> stmtsThatPrintVarName =
      pkbReader.getStmtsThatPrint(attrRefValue);

  if (stmtsThatPrintVarName.size() == 0) {
    // print.varName = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  // TODO (houten) integrate with synonymRes
  //vector<SynonymRes> printSynonymResColData;

  //// create read synonymRes objs
  //for (string stmtNum : stmtsThatReadVarName) {
  //  SynonymRes printSynonymRes =
  //      SynonymResFactory::buildPrintSynonym(stmtNum, attrRefValue);
  //  printSynonymResColData.push_back(printSynonymRes);
  //}

  //return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                    printSynonymResColData);
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

// for print.stmt#
IntermediateTable WithClause::evaluatePrintStmtNum(PKBReader& pkbReader) {
   vector<string> varPrintedByStmtNum =
   pkbReader.getVariablePrintedBy(std::stoi(attrRefValue));

   if (varPrintedByStmtNum.size() == 0) {
     // r.stmt# = attrRefVal does not exist
     return IntermediateTableFactory::buildEmptyIntermediateTable();
   }

  // TODO (houten) integrate with synonymRes
  
  // vector<SynonymRes> printSynonymResColData;

  //// create read synonymRes objs
  // for (int i = 0; i < varPrintedByStmtNum.size(); i++) {
  //   SynonymRes printSynonymRes = SynonymResFactory::buildPrintSynonym(
  //       attrRefValue, varPrintedByStmtNum);
  //   printSynonymResColData.push_back(printSynonymRes);
  // }
  // 
  // return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                      printSynonymResColData);
  return IntermediateTableFactory::buildEmptyIntermediateTable();
}
