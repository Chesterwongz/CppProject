#include "StmtOrProcToVarReader.h"

// (1, v)
std::vector<std::string> StmtOrProcToVarReader::getVarByStmt(int stmt) {
  return ReaderUtils::readStrStore(
      !relationSStore.hasDirectSuccessors(stmt),
      [stmt, this]() { return relationSStore.getDirectSuccessors(stmt); });
}

// (s, "name")
std::vector<std::string> StmtOrProcToVarReader::getStmtByVar(
    const std::string& varName, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) ||
      !relationSStore.hasDirectAncestors(varName)) {
    return {};
  }
  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  const auto& rawRes = relationSStore.getDirectAncestors(varName);

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
      !relationPStore.hasDirectSuccessors(procName), [procName, this]() {
        return relationPStore.getDirectSuccessors(procName);
      });
}

std::vector<std::string> StmtOrProcToVarReader::getProcByVar(
    const std::string& varName) {
  return ReaderUtils::readStrStore(
      !relationPStore.hasDirectAncestors(varName), [varName, this]() {
        return relationPStore.getDirectAncestors(varName);
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
