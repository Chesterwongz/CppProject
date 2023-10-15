#include "ModifiesReader.h"

#include "common/utils/CollectionUtils.h"

// (1, v)
std::vector<std::string> ModifiesReader::getVariablesModifiedBy(int stmt) {
  auto varFilter = PredicateUtils::truePredicate<std::string>();

  auto rawRes = modifiesStore.getDirectSuccessor(stmt, varFilter);

  return rawRes;
}

// (s, "name")
std::vector<std::string> ModifiesReader::getStatementsModifying(const std::string& varName, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = modifiesStore.getDirectAncestor(varName, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

bool ModifiesReader::isVariableModifiedBy(int stmt, const std::string& varName) {
  return modifiesStore.hasDirectRelation(stmt, varName);
}

std::vector<std::pair<std::string, std::string>> ModifiesReader::getModifiesPairs(
    StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto filters = std::make_pair(stmtStore.getStmtFilterPredicate(stmtType),
                                PredicateUtils::truePredicate<std::string>());

  auto rawRes = modifiesStore.getAllRelations(filters);

  return CollectionUtils::transformIntStrToStrStrVector(rawRes);
}

// =================================== ModifiesP ===================================

std::unordered_set<std::string> ModifiesReader::getModifiedVariablesForProc(
    const std::string& procName) {
  return {};
}
