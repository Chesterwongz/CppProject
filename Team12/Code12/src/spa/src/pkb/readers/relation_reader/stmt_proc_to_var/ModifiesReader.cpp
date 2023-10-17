#include "ModifiesReader.h"

#include "common/utils/CollectionUtils.h"

// (1, v)
std::vector<std::string> ModifiesReader::getVariablesModifiedBy(int stmt) {
  return {};
}

// (s, "name")
std::vector<std::string> ModifiesReader::getStatementsModifying(
    const std::string& varName, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }
  return {};
}

bool ModifiesReader::isVariableModifiedBy(int stmt,
                                          const std::string& varName) {
  return modifiesStore.hasDirectRelation(stmt, varName);
}

std::vector<std::pair<std::string, std::string>>
ModifiesReader::getModifiesPairs(StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  return {};
}

// ======================== ModifiesP ========================

std::unordered_set<std::string> ModifiesReader::getModifiedVariablesForProc(
    const std::string& procName) {
  return {};
}
