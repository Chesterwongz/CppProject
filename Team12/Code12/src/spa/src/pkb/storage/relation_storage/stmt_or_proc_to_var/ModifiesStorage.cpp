#include "ModifiesStorage.h"

void ModifiesStorage::addModifies(const std::string& varName,
                                  int stmtNum) {
  storage_.setRelatedVar(varName, stmtNum);
}

std::set<int> ModifiesStorage::getStmtsModifyingVar(
    const std::string& varName) {
  return storage_.getStmtNumForVar(varName);
}

std::set<std::string> ModifiesStorage::getVarsModifiedByStmt(
    int stmtNum) {
  return storage_.getVarForStmt(stmtNum);
}

std::set<std::string> ModifiesStorage::getAllVarsModifiedByStmt() {
  return storage_.getAllVarOfStmts();
}

std::set<int> ModifiesStorage::getAllStmtsModifyingVar() {
  return storage_.getAllStmtsOfVar();
}
