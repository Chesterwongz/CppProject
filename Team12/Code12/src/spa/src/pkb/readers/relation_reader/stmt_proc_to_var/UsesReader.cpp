#include "UsesReader.h"

// (1, v)
std::vector<std::string> UsesReader::getVariablesUsedBy(int stmt) {
  auto varFilter = PredicateUtils::truePredicate<std::string>();

  auto rawRes = usesStore.getDirectSuccessor(stmt, varFilter);

  return rawRes;
}

// (s, "name")
std::vector<std::string> UsesReader::getStatementsUsing(
    const std::string& varName, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = usesStore.getDirectAncestor(varName, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

bool UsesReader::isVariableUsedBy(int stmt, const std::string& varName) {
  return usesStore.hasDirectRelation(stmt, varName);
}

std::vector<std::pair<std::string, std::string>> UsesReader::getUsesPairs(
    StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto filters = std::make_pair(stmtStore.getStmtFilterPredicate(stmtType),
                                PredicateUtils::truePredicate<std::string>());

  auto rawRes = usesStore.getAllRelations(filters);

  return CollectionUtils::transformIntStrToStrStrVector(rawRes);
}

// =================================== UsesP ===================================

std::unordered_set<std::string> UsesReader::getUsedVariablesForProc(
    const std::string& procName) {
  return {};
}
