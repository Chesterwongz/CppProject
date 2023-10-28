#include "NotDecorator.h"

#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable NotDecorator::evaluate(PKBReader& pkb) {
  IntermediateTable wrapeeClauseResult = wrapeeClause->evaluate(pkb);

  vector<unique_ptr<AbstractArgument>> wrapeeClauseArgs =
      wrapeeClause->getAllArguments();

  IntermediateTable biggerTable = generateBiggerTable(pkb, wrapeeClauseArgs);

  IntermediateTable notResult = biggerTable.getDifference(wrapeeClauseResult);

  return notResult;
}

IntermediateTable NotDecorator::generateBiggerTable(
    PKBReader& pkb, vector<unique_ptr<AbstractArgument>>& wrapeeClauseArgs) {

  IntermediateTable biggerTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();

  for (int i = 0; i < wrapeeClauseArgs.size(); i++) {
    unique_ptr<AbstractArgument> wrapeeClauseArg =
        std::move(wrapeeClauseArgs[i]);

    if (!wrapeeClauseArg->isSynonym()) {
      // not synonym, ignore
      continue;
    }

    unique_ptr<SynonymArg> wrapeeClauseSynArg =
        unique_ptr<SynonymArg>(dynamic_cast<SynonymArg*>(wrapeeClauseArg.release()));

    vector<SynonymRes> synonymResObjsOfEntityType =
        notDecoratorFuncMap[wrapeeClauseSynArg->getEntityType()](pkb);

    IntermediateTable tableOfEntityType =
        IntermediateTableFactory::buildSingleColTable(
            wrapeeClauseSynArg->getValue(), synonymResObjsOfEntityType);

    biggerTable = biggerTable.join(tableOfEntityType);
  }

  return biggerTable;
}

bool NotDecorator::isEquals(const Clause& other) { 
  const auto* otherDecorator = dynamic_cast<const NotDecorator*>(&other);

  if (!otherDecorator) return false;

  return wrapeeClause->isEquals(*otherDecorator->wrapeeClause);
}

vector<SynonymRes> NotDecorator::getAllStmts(PKBReader& pkb) {
  vector<string> allStmts = pkb.getAllStmtsOf(StmtType::STMT);

  vector<SynonymRes> stmtSynonymResVec;

  for (string stmtNum : allStmts) {
    stmtSynonymResVec.push_back(SynonymResFactory::buildStmtSynonym(stmtNum));
  }
  return stmtSynonymResVec;
}

vector<SynonymRes> NotDecorator::getAllAssignStmts(PKBReader& pkb) {
  vector<string> allAssignStmts = pkb.getAllStmtsOf(StmtType::ASSIGN);

  vector<SynonymRes> assignStmtSynonymResVec;

  for (string stmtNum : allAssignStmts) {
    assignStmtSynonymResVec.push_back(
        SynonymResFactory::buildStmtSynonym(stmtNum));
  }
  return assignStmtSynonymResVec;
}

vector<SynonymRes> NotDecorator::getAllWhileStmts(PKBReader& pkb) {
  vector<string> allWhileStmts = pkb.getAllStmtsOf(StmtType::WHILE);

  vector<SynonymRes> whileStmtSynonymResVec;

  for (string stmtNum : allWhileStmts) {
    whileStmtSynonymResVec.push_back(
        SynonymResFactory::buildStmtSynonym(stmtNum));
  }
  return whileStmtSynonymResVec;
}

vector<SynonymRes> NotDecorator::getAllIfStmts(PKBReader& pkb) {
  vector<string> allIfStmts = pkb.getAllStmtsOf(StmtType::IF);

  vector<SynonymRes> ifStmtSynonymResVec;

  for (string stmtNum : allIfStmts) {
    ifStmtSynonymResVec.push_back(
        SynonymResFactory::buildStmtSynonym(stmtNum));
  }
  return ifStmtSynonymResVec;
}

vector<SynonymRes> NotDecorator::getAllPrintStmts(PKBReader& pkb) {
  vector<string> allPrintStmts = pkb.getAllStmtsOf(StmtType::PRINT);

  vector<SynonymRes> printStmtSynonymResVec;

  for (string stmtNum : allPrintStmts) {
    vector<string> varsPrintedBy = pkb.getVariablePrintedBy(std::stoi(stmtNum));
    for (string varName : varsPrintedBy) {
      printStmtSynonymResVec.push_back(
          SynonymResFactory::buildPrintSynonym(stmtNum, varName));
    }
  }
  return printStmtSynonymResVec;
}

vector<SynonymRes> NotDecorator::getAllReadStmts(PKBReader& pkb) {
  vector<string> allReadStmts = pkb.getAllStmtsOf(StmtType::READ);

  vector<SynonymRes> readStmtSynonymResVec;

  for (string stmtNum : allReadStmts) {
    vector<string> varsReadBy = pkb.getVariableReadBy(std::stoi(stmtNum));
    for (string varName : varsReadBy) {
      readStmtSynonymResVec.push_back(
          SynonymResFactory::buildReadSynonym(stmtNum, varName));
    }
  }
  return readStmtSynonymResVec;
}

vector<SynonymRes> NotDecorator::getAllCallStmts(PKBReader& pkb) {
  vector<string> allCallStmts = pkb.getAllStmtsOf(StmtType::CALL);

  vector<SynonymRes> callStmtSynonymResVec;

  for (string stmtNum : allCallStmts) {
    vector<string> procsCalledBy = pkb.getProcCalledBy(std::stoi(stmtNum));
    for (string procName : procsCalledBy) {
      callStmtSynonymResVec.push_back(
          SynonymResFactory::buildCallsSynonym(stmtNum, procName));
    }
  }
  return callStmtSynonymResVec;
}

vector<SynonymRes> NotDecorator::getAllConstants(PKBReader& pkb) {
  vector<string> allConstants = pkb.getAllConstants();

  vector<SynonymRes> constantSynonymResVec;

  for (string constant : allConstants) {
    constantSynonymResVec.push_back(
        SynonymResFactory::buildConstantSynonym(constant));
  }

  return constantSynonymResVec;
}

vector<SynonymRes> NotDecorator::getAllProcedures(PKBReader& pkb) {
  vector<string> allprocs = pkb.getAllProcedures();

  vector<SynonymRes> procSynonymResVec;

  for (string procName : allprocs) {
    procSynonymResVec.push_back(
        SynonymResFactory::buildConstantSynonym(procName));
  }

  return procSynonymResVec;
}

vector<SynonymRes> NotDecorator::getAllVariables(PKBReader& pkb) {
  vector<string> allVars = pkb.getAllVariables();

  vector<SynonymRes> varSynonymResVec;

  for (string varName : allVars) {
    varSynonymResVec.push_back(
        SynonymResFactory::buildVarSynonym(varName));
  }

  return varSynonymResVec;
}
