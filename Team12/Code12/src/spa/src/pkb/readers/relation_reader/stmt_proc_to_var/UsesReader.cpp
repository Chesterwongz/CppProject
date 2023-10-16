#include "UsesReader.h"

// (1, v)
std::vector<std::string> UsesReader::getVariablesUsedBy(int stmt) {
  auto rawRes = usesStore.getAllDirectSuccessorsOf(stmt);

  return rawRes;
}

// (s, "name")
std::vector<std::string> UsesReader::getStatementsUsing(
    const std::string& varName, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = usesStore.getDirectAncestorsOf(varName, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

bool UsesReader::isVariableUsedBy(int stmt, const std::string& varName) {
  return usesStore.hasDirectRelation(stmt, varName);
}

std::vector<std::pair<std::string, std::string>> UsesReader::getUsesPairs(
    StmtType stmtType1) {
  if (!stmtStore.hasStmtType(stmtType1)) {
    return {};
  }

  auto filters = stmtStore.getStmtStrFilterPredicates(stmtType1);

  auto rawRes = usesStore.getDirectRelations(filters);

  return CollectionUtils::transformIntStrToStrStrVector(rawRes);
}

// =================================== UsesP ===================================

std::unordered_set<std::string> UsesReader::getUsedVariablesForProc(
    const std::string& procName) {
  return {};
}
