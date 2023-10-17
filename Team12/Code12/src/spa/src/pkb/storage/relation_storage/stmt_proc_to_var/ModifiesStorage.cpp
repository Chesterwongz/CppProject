#include "ModifiesStorage.h"

void ModifiesStorage::addModifies(const std::string& varName, int stmtNum) {
  storage_.setRelatedVar(varName, stmtNum);
}

void ModifiesStorage::addModifies(const std::string& varName,
                                  const std::string& procName) {
  storage_.setRelatedVar(varName, procName);
}

std::set<int> ModifiesStorage::getStmtsModifyingVar(
    const std::string& varName) {
  return storage_.getStmtNumForVar(varName);
}

std::unordered_set<std::string> ModifiesStorage::getProcsModifyingVar(
    const std::string& variableName) {
  return storage_.getProcsForVar(variableName);
}

std::set<std::string> ModifiesStorage::getVarsModifiedByStmt(int stmtNum) {
  return storage_.getVarForStmt(stmtNum);
}

std::unordered_set<std::string> ModifiesStorage::getVarsModifiedByProc(
    const std::string& procName) {
  return storage_.getVarsForProc(procName);
}

std::set<std::string> ModifiesStorage::getAllVarsModifiedByStmt() {
  return storage_.getAllVarOfStmts();
}

std::set<int> ModifiesStorage::getAllStmtsModifyingVar() {
  return storage_.getAllStmtsOfVar();
}
