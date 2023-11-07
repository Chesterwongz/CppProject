#include "NotDecorator.h"

#include <string>
#include <vector>

#include "qps/intermediateTable/IntermediateTableFactory.h"

IntermediateTable NotDecorator::evaluate(PKBReader& pkb) {
  IntermediateTable wrapeeClauseResult = wrapeeClause->evaluate(pkb);

  vector<const AbstractArgument*> wrapeeClauseArgs =
      wrapeeClause->getAllArguments();

  IntermediateTable minuend = generateMinuend(pkb, wrapeeClauseArgs);

  IntermediateTable notResult = minuend.getDifference(wrapeeClauseResult);

  return notResult;
}

IntermediateTable NotDecorator::generateMinuend(
    PKBReader& pkb, vector<const AbstractArgument*>& wrapeeClauseArgs) {
  IntermediateTable minuend =
      IntermediateTableFactory::buildWildcardIntermediateTable();

  for (auto wrapeeClauseArg : wrapeeClauseArgs) {
    if (!wrapeeClauseArg->isSynonym()) {
      // not synonym, ignore
      continue;
    }

    SynonymArg* wrapeeClauseSynArg = dynamic_cast<SynonymArg*>(
        const_cast<AbstractArgument*>(wrapeeClauseArg));

    vector<std::reference_wrapper<SynonymRes>> synonymResObjsOfEntityType =
        notDecoratorFuncMap[wrapeeClauseSynArg->getEntityType()](pkb);

    IntermediateTable tableOfEntityType =
        IntermediateTableFactory::buildSingleColTable(
            wrapeeClauseSynArg->getValue(), synonymResObjsOfEntityType);

    minuend = minuend.join(tableOfEntityType);
  }

  return minuend;
}

bool NotDecorator::isEquals(const IClause& other) {
  const auto* otherDecorator = dynamic_cast<const NotDecorator*>(&other);

  if (!otherDecorator) return false;

  return wrapeeClause->isEquals(*otherDecorator->wrapeeClause);
}

vector<std::reference_wrapper<SynonymRes>> NotDecorator::getStmtSynonyms(
    vector<std::string>& stmts) {
  vector<std::reference_wrapper<SynonymRes>> stmtSynonymResVec {};
  stmtSynonymResVec.reserve(stmts.size());
  for (const string& stmtNum : stmts) {
    stmtSynonymResVec.emplace_back(
        SynonymResFactory::buildStmtSynonym(stmtNum));
  }
  return stmtSynonymResVec;
}

vector<std::reference_wrapper<SynonymRes>> NotDecorator::getAllStmts(
    PKBReader& pkb) {
  vector<string> allStmts = pkb.getAllStmtsOf(StmtType::STMT);
  return getStmtSynonyms(allStmts);
}

vector<std::reference_wrapper<SynonymRes>> NotDecorator::getAllAssignStmts(
    PKBReader& pkb) {
  vector<string> allAssignStmts = pkb.getAllStmtsOf(StmtType::ASSIGN);
  return getStmtSynonyms(allAssignStmts);
}

vector<std::reference_wrapper<SynonymRes>> NotDecorator::getAllWhileStmts(
    PKBReader& pkb) {
  vector<string> allWhileStmts = pkb.getAllStmtsOf(StmtType::WHILE);
  return getStmtSynonyms(allWhileStmts);
}

vector<std::reference_wrapper<SynonymRes>> NotDecorator::getAllIfStmts(
    PKBReader& pkb) {
  vector<string> allIfStmts = pkb.getAllStmtsOf(StmtType::IF);
  return getStmtSynonyms(allIfStmts);
}

vector<std::reference_wrapper<SynonymRes>> NotDecorator::getAllPrintStmts(
    PKBReader& pkb) {
  vector<string> allPrintStmts = pkb.getAllStmtsOf(StmtType::PRINT);

  vector<std::reference_wrapper<SynonymRes>> printStmtSynonymResVec {};

  for (const string& stmtNum : allPrintStmts) {
    vector<string> varsPrintedBy = pkb.getVariablePrintedBy(std::stoi(stmtNum));
    for (const string& varName : varsPrintedBy) {
      printStmtSynonymResVec.emplace_back(
          SynonymResFactory::buildPrintSynonym(stmtNum, varName));
    }
  }
  return printStmtSynonymResVec;
}

vector<std::reference_wrapper<SynonymRes>> NotDecorator::getAllReadStmts(
    PKBReader& pkb) {
  vector<string> allReadStmts = pkb.getAllStmtsOf(StmtType::READ);

  vector<std::reference_wrapper<SynonymRes>> readStmtSynonymResVec {};

  for (const string& stmtNum : allReadStmts) {
    vector<string> varsReadBy = pkb.getVariableReadBy(std::stoi(stmtNum));
    for (const string& varName : varsReadBy) {
      readStmtSynonymResVec.emplace_back(
          SynonymResFactory::buildReadSynonym(stmtNum, varName));
    }
  }
  return readStmtSynonymResVec;
}

vector<std::reference_wrapper<SynonymRes>> NotDecorator::getAllCallStmts(
    PKBReader& pkb) {
  vector<string> allCallStmts = pkb.getAllStmtsOf(StmtType::CALL);

  vector<std::reference_wrapper<SynonymRes>> callStmtSynonymResVec {};

  for (const string& stmtNum : allCallStmts) {
    vector<string> procsCalledBy = pkb.getProcCalledBy(std::stoi(stmtNum));
    for (const string& procName : procsCalledBy) {
      callStmtSynonymResVec.emplace_back(
          SynonymResFactory::buildCallsSynonym(stmtNum, procName));
    }
  }
  return callStmtSynonymResVec;
}

vector<std::reference_wrapper<SynonymRes>> NotDecorator::getAllConstants(
    PKBReader& pkb) {
  vector<string> allConstants = pkb.getAllConstants();

  vector<std::reference_wrapper<SynonymRes>> constantSynonymResVec {};
  constantSynonymResVec.reserve(allConstants.size());
  for (const string& constant : allConstants) {
    constantSynonymResVec.emplace_back(
        SynonymResFactory::buildConstantSynonym(constant));
  }

  return constantSynonymResVec;
}

vector<std::reference_wrapper<SynonymRes>> NotDecorator::getAllProcedures(
    PKBReader& pkb) {
  vector<string> allprocs = pkb.getAllProcedures();

  vector<std::reference_wrapper<SynonymRes>> procSynonymResVec {};
  procSynonymResVec.reserve(allprocs.size());
  for (const string& procName : allprocs) {
    procSynonymResVec.emplace_back(
        SynonymResFactory::buildProcSynonym(procName));
  }

  return procSynonymResVec;
}

vector<std::reference_wrapper<SynonymRes>> NotDecorator::getAllVariables(
    PKBReader& pkb) {
  vector<string> allVars = pkb.getAllVariables();

  vector<std::reference_wrapper<SynonymRes>> varSynonymResVec {};
  varSynonymResVec.reserve(allVars.size());
  for (const string& varName : allVars) {
    varSynonymResVec.emplace_back(SynonymResFactory::buildVarSynonym(varName));
  }

  return varSynonymResVec;
}
