#include "ModifiesReader.h"

// (1, v)
std::vector<std::string> ModifiesReader::getVariablesModifiedBy(int stmt) {
  return modifiesSStore.getAllDirectSuccessorsOf(stmt);
}

// (s, "name")
std::vector<std::string> ModifiesReader::getStatementsModifying(
    const std::string& varName, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }
  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = modifiesSStore.getDirectAncestorsOf(varName, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

bool ModifiesReader::isVariableModifiedBy(int stmt,
                                          const std::string& varName) {
  return modifiesSStore.hasDirectRelation(stmt, varName);
}

std::vector<std::pair<std::string, std::string>>
ModifiesReader::getModifiesStmtPairs(StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto filters = stmtStore.getStmtStrFilterPredicates(stmtType);

  auto rawRes = modifiesSStore.getDirectRelations(filters);

  return CollectionUtils::transformIntStrToStrStrVector(rawRes);
}

// ================================= ModifiesP =================================

std::vector<std::string> ModifiesReader::getVarsModifiedByProc(
    const string& procName) {
  return modifiesPStore.getAllDirectSuccessorsOf(procName);
}
std::vector<std::string> ModifiesReader::getProcModifying(
    const string& varName) {
  return modifiesPStore.getAllDirectAncestorsOf(varName);
}
bool ModifiesReader::isVariableModifiedByProc(const string& procName,
                                              const string& varName) {
  return modifiesPStore.hasDirectRelation(procName, varName);
}
std::vector<std::pair<std::string, std::string>>
ModifiesReader::getModifiesProcPairs() {
  return modifiesPStore.getAllDirectRelations();
}
