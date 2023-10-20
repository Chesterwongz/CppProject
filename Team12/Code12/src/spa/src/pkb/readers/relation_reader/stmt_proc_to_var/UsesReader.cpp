#include "UsesReader.h"

// (1, v)
std::vector<std::string> UsesReader::getVariablesUsedBy(int stmt) {
  if (!usesSStore.hasDirectSuccessor(stmt)) {
    return {};
  }
  const auto& rawRes = usesSStore.getDirectSuccessors(stmt);
  return {rawRes.begin(), rawRes.end()};
}

// (s, "name")
std::vector<std::string> UsesReader::getStatementsUsing(
    const std::string& varName, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) ||
      !usesSStore.hasDirectAncestor(varName)) {
    return {};
  }
  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  const auto& rawRes = usesSStore.getDirectAncestors(varName);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

bool UsesReader::isVariableUsedBy(int stmt, const std::string& varName) {
  return usesSStore.hasDirectRelation(stmt, varName);
}

std::vector<std::pair<std::string, std::string>> UsesReader::getUsesStmtPairs(
    StmtType stmtType1) {
  if (!stmtStore.hasStmtType(stmtType1)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType1);

  const auto& rawRes = usesSStore.getDirectRelations();

  return CollectionUtils::transformMapSetABToVectorUB<int, std::string,
                                                      std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

// =================================== UsesP ===================================

std::vector<std::string> UsesReader::getVarsUsedByProc(
    const std::string& procName) {
  if (!usesPStore.hasDirectSuccessor(procName)) {
    return {};
  }
  const auto& rawRes = usesPStore.getDirectSuccessors(procName);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> UsesReader::getProcUsing(const std::string& varName) {
  if (!usesPStore.hasDirectAncestor(varName)) {
    return {};
  }
  const auto& rawRes = usesPStore.getDirectAncestors(varName);
  return {rawRes.begin(), rawRes.end()};
}

bool UsesReader::isVariableUsedByProc(const std::string& procName,
                                      const std::string& varName) {
  return usesPStore.hasDirectRelation(procName, varName);
}

std::vector<std::pair<std::string, std::string>>
UsesReader::getUsesProcPairs() {
  const auto& rawRes = usesPStore.getDirectRelations();
  return CollectionUtils::transformMapSetABToVectorAB<std::string, std::string>(
      rawRes);
}
