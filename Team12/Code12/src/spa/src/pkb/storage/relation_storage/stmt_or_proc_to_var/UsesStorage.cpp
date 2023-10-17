#include "UsesStorage.h"

void UsesStorage::addUses(const std::string& variableName,
                          int statementNumber) {
  storage_.setRelatedVar(variableName, statementNumber);
}

void UsesStorage::addUses(const std::string& variableName,
                          const std::string& procName) {
  storage_.setRelatedVar(variableName, procName);
}

std::set<int> UsesStorage::getStmtsUsingVar(const std::string& variableName) {
  return storage_.getStmtNumForVar(variableName);
}

std::unordered_set<std::string> UsesStorage::getProcsUsingVar(
    const std::string& variableName) {
  return storage_.getProcsForVar(variableName);
}

std::set<std::string> UsesStorage::getVarsUsedByStmt(int statementNumber) {
  return storage_.getVarForStmt(statementNumber);
}

std::unordered_set<std::string> UsesStorage::getVarsUsedByProc(
    const std::string& procName) {
  return storage_.getVarsForProc(procName);
}

std::set<std::string> UsesStorage::getAllVarUsedByStmt() {
  return storage_.getAllVarOfStmts();
}

std::set<int> UsesStorage::getAllStmtUsingVar() {
  return storage_.getAllStmtsOfVar();
}
