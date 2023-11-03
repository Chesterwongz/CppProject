#include "ModifiesReader.h"

// (1, v)
std::vector<std::string> ModifiesReader::getVariablesModifiedBy(int stmt) {
  if (!modifiesSStore.hasDirectSuccessors(stmt)) {
    return {};
  }
  const auto& rawRes = modifiesSStore.getDirectSuccessors(stmt);
  return {rawRes.begin(), rawRes.end()};
}

// (s, "name")
std::vector<std::string> ModifiesReader::getStatementsModifying(
    const std::string& varName, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) ||
      !modifiesSStore.hasDirectAncestors(varName)) {
    return {};
  }
  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  const auto& rawRes = modifiesSStore.getDirectAncestors(varName);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
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

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  const auto& rawRes = modifiesSStore.getDirectSuccessorMap();

  return CollectionUtils::intStrMapSetToStrPairVector(rawRes, stmtFilter);
}

// ================================= ModifiesP =================================

std::vector<std::string> ModifiesReader::getVarsModifiedByProc(
    const string& procName) {
  if (!modifiesPStore.hasDirectSuccessors(procName)) {
    return {};
  }
  const auto& rawRes = modifiesPStore.getDirectSuccessors(procName);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> ModifiesReader::getProcModifying(
    const string& varName) {
  if (!modifiesPStore.hasDirectAncestors(varName)) {
    return {};
  }
  const auto& rawRes = modifiesPStore.getDirectAncestors(varName);
  return {rawRes.begin(), rawRes.end()};
}
bool ModifiesReader::isVariableModifiedByProc(const string& procName,
                                              const string& varName) {
  return modifiesPStore.hasDirectRelation(procName, varName);
}
std::vector<std::pair<std::string, std::string>>
ModifiesReader::getModifiesProcPairs() {
  const auto& rawRes = modifiesPStore.getDirectSuccessorMap();
  return CollectionUtils::mapSetToPairVector<std::string, std::string>(rawRes);
}
