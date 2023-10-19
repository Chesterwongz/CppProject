#include "qps/clause/withClause/WithClause.h"

#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable WithClause::evaluate(Context& context, PKBReader& pkb) {
  pair<string, string> entity_attrRef_pair = make_pair(synonymEntity, attrRef);

  IntermediateTable pkbResult =
      withEvaluatorFuncMap[entity_attrRef_pair](pkb);

  return pkbResult;
}

IntermediateTable WithClause::evaluateStmtNum(PKBReader& pkbReader) {
  StmtType stmtType = StmtEntityToStatementType.at(synonymEntity);
  bool isValidStmt = pkbReader.isValidStatement(attrRefValue, stmtType);

  if (!isValidStmt) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};

  return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
                                                       result);
}

IntermediateTable WithClause::evaluateConstantValue(PKBReader& pkbReader) {
  bool isValidConstant = pkbReader.isValidConstant(attrRefValue);

  if (!isValidConstant) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};

  return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
                                                       result);
}

IntermediateTable WithClause::evaluateProcName(PKBReader& pkbReader) {
  bool isValidProcName = pkbReader.isValidProcName(attrRefValue);

  if (!isValidProcName) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};

  return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
                                                       result);
}

IntermediateTable WithClause::evaluateVarName(PKBReader& pkbReader) {
  bool isValidVariable = pkbReader.isValidVariable(attrRefValue);

  if (!isValidVariable) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  vector<string> result = {attrRefValue};

  return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
                                                       result);
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
  //vector<SynonymRes> callsSynonymResColData;

  //// create call synonymRes objs
  //for (string stmtNum : stmtsThatCallProcName) {
  //  
  //  SynonymRes callsSynonymRes = SynonymResFactory::buildCallsSynonym(stmtNum, attrRefValue);
  //  callsSynonymResColData.push_back(callsSynonymRes);
  //}

  //return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                     callsSynonymResColData);
}

// for call.stmtNum
IntermediateTable WithClause::evaluateCallStmtNum(PKBReader& pkbReader) {
  string procNameCalledByStmtNum =
      pkbReader.getProcCalledByStmt(std::stoi(attrRefValue));

  if (procNameCalledByStmtNum.empty()) {
    // c.stmtNum = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable(); 
  }
  // TODO integrate with synonymRes

  //vector<SynonymRes> callsSynonymResColData;
  //
  //// create call synonymRes objs
  //
  //SynonymRes callsSynonymRes =
  //    SynonymResFactory::buildCallsSynonym(attrRefValue, procNameCalledByStmtNum);
  //callsSynonymResColData.push_back(callsSynonymRes);

  //return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                     callsSynonymResColData);
}

// for read.varName
IntermediateTable WithClause::evaluateReadVarName(PKBReader& pkbReader) {
  vector<string> stmtsThatReadVarName =
      pkbReader.getStmtsThatRead(attrRefValue);

  if (stmtsThatReadVarName.size() == 0) {
    // r.varName = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  // TODO: integrate with synonymRes

  //vector<SynonymRes> readSynonymResColData;
  //
  //// create read synonymRes objs
  //for (string stmtNum : stmtsThatReadVarName) {
  //  
  //  SynonymRes readSynonymRes =
  //      SynonymResFactory::buildReadSynonym(stmtNum, attrRefValue);
  //  readSynonymResColData.push_back(readSynonymRes);
  //}

  //return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                     readSynonymResColData);
}

// for read.stmt#
IntermediateTable WithClause::evaluateReadStmtNum(PKBReader& pkbReader) {
  string varReadByStmtNum = pkbReader.getVariableReadBy(std::stoi(attrRefValue));

  if (varReadByStmtNum.empty()) {
    // r.stmt# = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  //// TODO: integrate with synonymRes
  //vector<SynonymRes> readSynonymResColData;

  //// create read synonymRes objs
  //SynonymRes readSynonymRes =
  //    SynonymResFactory::buildReadSynonym(attrRefValue, varReadByStmtNum);
  //readSynonymResColData.push_back(readSynonymRes);


  //return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                     readSynonymResColData);
}

// for print.varName
IntermediateTable WithClause::evaluatePrintVarName(PKBReader& pkbReader) {
  vector<string> stmtsThatPrintVarName =
      pkbReader.getStmtsThatPrint(attrRefValue);

  if (stmtsThatPrintVarName.size() == 0) {
    // print.varName = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  // TODO: integrate with synonymRes
  //vector<SynonymRes> printSynonymResColData;

  //// create read synonymRes objs
  //for (string stmtNum : stmtsThatReadVarName) {
  //  
  //  SynonymRes printSynonymRes =
  //      SynonymResFactory::buildPrintSynonym(stmtNum, attrRefValue);
  //  printSynonymResColData.push_back(printSynonymRes);
  //}

  //return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                     printSynonymResColData);
}

// for print.stmt#
IntermediateTable WithClause::evaluatePrintStmtNum(PKBReader& pkbReader) {
  string varPrintedByStmtNum = pkbReader.getVariablePrintedBy(std::stoi(attrRefValue));

  if (varPrintedByStmtNum.empty()) {
    // r.stmt# = attrRefVal does not exist
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  //// TODO: integrate with synonymRes
  // 
  //vector<SynonymRes> printSynonymResColData;

  //// create read synonymRes objs
  //SynonymRes printSynonymRes =
  //    SynonymResFactory::buildPrintSynonym(attrRefValue, varPrintedByStmtNum);
  //printSynonymResColData.push_back(printSynonymRes);

  //return IntermediateTableFactory::buildSingleColTable(synonym->getValue(),
  //                                                     printSynonymResColData);
}
