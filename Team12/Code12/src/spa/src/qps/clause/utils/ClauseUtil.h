#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/StmtTypes.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/common/Keywords.h"
#include "qps/intermediateTable/synonymRes/SynonymResFactory.h"

using std::string, std::unordered_map, std::set, std::reference_wrapper,
    std::vector;

class Clause;
namespace ClauseUtil {
typedef vector<unique_ptr<Clause>> ClauseList;
typedef vector<reference_wrapper<unique_ptr<Clause>>> ClauseRefList;

static Entity getArgEntity(AbstractArgument& arg) {
  if (arg.isSynonym()) {
    return dynamic_cast<SynonymArg&>(arg).getEntityType();
  }
  return INVALID_ENTITY;
}

static set<string> getSynonymArgValues(unique_ptr<AbstractArgument>& arg1,
                                       unique_ptr<AbstractArgument>& arg2) {
  set<string> res = {};
  if (arg1->isSynonym()) {
    res.insert(arg1->getValue());
  }
  if (arg2->isSynonym()) {
    res.insert(arg2->getValue());
  }
  return res;
}

static vector<std::reference_wrapper<SynonymRes>> getAllStmts(PKBReader& pkb) {
  vector<string> allStmts = pkb.getAllStmtsOf(StmtType::STMT);
  return SynonymResFactory::buildStmtSynonymResVector(allStmts);
}

static vector<std::reference_wrapper<SynonymRes>> getAllAssignStmts(
    PKBReader& pkb) {
  vector<string> allAssignStmts = pkb.getAllStmtsOf(StmtType::ASSIGN);
  return SynonymResFactory::buildStmtSynonymResVector(allAssignStmts);
}

static vector<std::reference_wrapper<SynonymRes>> getAllWhileStmts(
    PKBReader& pkb) {
  vector<string> allWhileStmts = pkb.getAllStmtsOf(StmtType::WHILE);
  return SynonymResFactory::buildStmtSynonymResVector(allWhileStmts);
}

static vector<std::reference_wrapper<SynonymRes>> getAllIfStmts(
    PKBReader& pkb) {
  vector<string> allIfStmts = pkb.getAllStmtsOf(StmtType::IF);
  return SynonymResFactory::buildStmtSynonymResVector(allIfStmts);
}

static vector<std::reference_wrapper<SynonymRes>> getAllPrintStmts(
    PKBReader& pkb) {
  vector<pair<string, string>> allPrintVarNamePairs =
      pkb.getAllStmtVarPrintPairs();

  vector<std::reference_wrapper<SynonymRes>> printSynonymResVec =
      SynonymResFactory::buildPrintSynonymResVector(allPrintVarNamePairs);

  return printSynonymResVec;
}

static vector<std::reference_wrapper<SynonymRes>> getAllReadStmts(
    PKBReader& pkb) {
  vector<pair<string, string>> allReadVarNamePairs =
      pkb.getAllStmtVarReadPairs();

  vector<std::reference_wrapper<SynonymRes>> readSynonymResVec =
      SynonymResFactory::buildReadSynonymResVector(allReadVarNamePairs);

  return readSynonymResVec;
}

static vector<std::reference_wrapper<SynonymRes>> getAllCallStmts(
    PKBReader& pkb) {
  vector<pair<string, string>> allCallProcNamePairs =
      pkb.getAllStmtProcCallsPairs();

  vector<std::reference_wrapper<SynonymRes>> callSynonymResVec =
      SynonymResFactory::buildCallSynonymResVector(allCallProcNamePairs);

  return callSynonymResVec;
}

static vector<std::reference_wrapper<SynonymRes>> getAllConstants(
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

static vector<std::reference_wrapper<SynonymRes>> getAllProcedures(
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

static vector<std::reference_wrapper<SynonymRes>> getAllVariables(
    PKBReader& pkb) {
  vector<string> allVars = pkb.getAllVariables();

  vector<std::reference_wrapper<SynonymRes>> varSynonymResVec {};
  varSynonymResVec.reserve(allVars.size());
  for (const string& varName : allVars) {
    varSynonymResVec.emplace_back(SynonymResFactory::buildVarSynonym(varName));
  }

  return varSynonymResVec;
}

const string KEY_DELIMITER = "|";
}  // namespace ClauseUtil


