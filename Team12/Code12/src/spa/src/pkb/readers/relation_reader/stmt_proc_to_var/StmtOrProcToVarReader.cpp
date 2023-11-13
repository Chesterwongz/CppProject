#include "StmtOrProcToVarReader.h"

// (1, v)
std::vector<std::string> StmtOrProcToVarReader::getVarByStmt(int stmt) {
  return ReaderUtils::readStrStore(
      stmt != common::WILDCARD_STMT_NUM &&
          !relationSStore.hasDirectSuccessors(stmt),
      [stmt, this]() {
        return stmt == common::WILDCARD_STMT_NUM
                   ? relationSStore.getDirectSuccessors()
                   : relationSStore.getDirectSuccessors(stmt);
      });
}

// (s, "name")
std::vector<std::string> StmtOrProcToVarReader::getStmtByVar(
    const std::string& varName, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) ||
      (varName != common::WILDCARD_VAR &&
       !relationSStore.hasDirectAncestors(varName))) {
    return {};
  }
  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);
  std::unordered_set<int> rawRes;
  if (varName == common::WILDCARD_VAR) {
    rawRes = relationSStore.getDirectAncestors();
  } else {
    rawRes = relationSStore.getDirectAncestors(varName);
  }

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

bool StmtOrProcToVarReader::hasDirectRelation(int stmt,
                                              const std::string& varName) {
  return relationSStore.hasDirectRelation(stmt, varName);
}

std::vector<std::pair<std::string, std::string>>
StmtOrProcToVarReader::getStmtVarPairs(StmtType stmtType1) {
  if (!stmtStore.hasStmtType(stmtType1)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType1);

  const auto& rawRes = relationSStore.getDirectSuccessorMap();

  return CollectionUtils::intStrMapSetToStrPairVector(rawRes, stmtFilter);
}

// ================================== P to V ==================================

std::vector<std::string> StmtOrProcToVarReader::getVarByProc(
    const std::string& procName) {
  return ReaderUtils::readStrStore(
      procName != common::WILDCARD_PROC &&
          !relationPStore.hasDirectSuccessors(procName),
      [procName, this]() {
        return procName == common::WILDCARD_PROC
                   ? relationPStore.getDirectSuccessors()
                   : relationPStore.getDirectSuccessors(procName);
      });
}

std::vector<std::string> StmtOrProcToVarReader::getProcByVar(
    const std::string& varName) {
  return ReaderUtils::readStrStore(
      varName != common::WILDCARD_VAR &&
          !relationPStore.hasDirectAncestors(varName),
      [varName, this]() {
        return varName == common::WILDCARD_VAR
                   ? relationPStore.getDirectAncestors()
                   : relationPStore.getDirectAncestors(varName);
      });
}

bool StmtOrProcToVarReader::hasDirectRelation(const std::string& procName,
                                              const std::string& varName) {
  return relationPStore.hasDirectRelation(procName, varName);
}

std::vector<std::pair<std::string, std::string>>
StmtOrProcToVarReader::getProcVarPairs() {
  const auto& rawRes = relationPStore.getDirectSuccessorMap();
  return CollectionUtils::mapSetToPairVector<std::string, std::string>(rawRes);
}
