#include "UsesStorage.h"

void UsesStorage::addUses(const std::string& variableName,
                                   int statementNumber) {
  storage_.setRelatedVar(variableName, statementNumber);
}

std::set<int> UsesStorage::getStmtsUsingVar(
    const std::string& variableName) {
  return storage_.getStmtNumForVar(variableName);
}

std::set<std::string> UsesStorage::getVarsUsedByStmt(
    int statementNumber) {
  return storage_.getVarForStmt(statementNumber);
}

std::set<std::string> UsesStorage::getAllVarUsedByStmt() {
  return storage_.getAllVarOfStmts();
}

std::set<int> UsesStorage::getAllStmtUsingVar() {
  return storage_.getAllStmtsOfVar();
}
