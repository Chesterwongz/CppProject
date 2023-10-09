#include "UsesReaderImpl.h"

std::set<std::string> UsesReaderImpl::getVarsRelatedToStmt(int stmtNum) {
  return uses_storage_.getVarsUsedByStmt(stmtNum);
}

std::set<int> UsesReaderImpl::getStmtsRelatedToVar(const std::string& varName) {
  return uses_storage_.getStmtsUsingVar(varName);
}
