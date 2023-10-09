#include "ModifiesReaderImpl.h"

std::set<std::string> ModifiesReaderImpl::getVarsRelatedToStmt(int stmtNum) {
  return modifies_storage_.getVarsModifiedByStmt(stmtNum);
}

std::set<int> ModifiesReaderImpl::getStmtsRelatedToVar(
    const std::string& varName) {
  return modifies_storage_.getStmtsModifyingVar(varName);
}
