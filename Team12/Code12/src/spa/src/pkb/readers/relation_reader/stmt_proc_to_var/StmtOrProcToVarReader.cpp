#include "StmtOrProcToVarReader.h"

// (1, v)
std::vector<std::string> StmtOrProcToVarReader::getVarByStmt(int stmt) {
  if (!relationSStore.hasDirectSuccessors(stmt)) {
    return {};
  }
  const auto& rawRes = relationSStore.getDirectSuccessors(stmt);
  return {rawRes.begin(), rawRes.end()};
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
  if (!relationPStore.hasDirectSuccessors(procName)) {
    return {};
  }
  const auto& rawRes = relationPStore.getDirectSuccessors(procName);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> StmtOrProcToVarReader::getProcByVar(
    const std::string& varName) {
  if (!relationPStore.hasDirectAncestors(varName)) {
    return {};
  }
  const auto& rawRes = relationPStore.getDirectAncestors(varName);
  return {rawRes.begin(), rawRes.end()};
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
