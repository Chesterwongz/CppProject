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
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = usesSStore.getDirectAncestorsOf(varName, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

bool UsesReader::isVariableUsedBy(int stmt, const std::string& varName) {
  return usesSStore.hasDirectRelation(stmt, varName);
}

std::vector<std::pair<std::string, std::string>> UsesReader::getUsesStmtPairs(
    StmtType stmtType1) {
  if (!stmtStore.hasStmtType(stmtType1)) {
    return {};
  }

  auto filters = stmtStore.getStmtStrFilterPredicates(stmtType1);

  auto rawRes = usesSStore.getDirectRelations(filters);

  return CollectionUtils::transformIntStrToStrStrVector(rawRes);
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
  return usesPStore.getAllDirectAncestorsOf(varName);
}

bool UsesReader::isVariableUsedByProc(const std::string& procName,
                                      const std::string& varName) {
  return usesPStore.hasDirectRelation(procName, varName);
}

std::vector<std::pair<std::string, std::string>>
UsesReader::getUsesProcPairs() {
  return usesPStore.getAllDirectRelations();
}
