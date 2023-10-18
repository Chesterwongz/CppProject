#include "UsesReaderImpl.h"

std::set<std::string> UsesReaderImpl::getVarsRelatedToStmt(int stmtNum) {
  return uses_storage_.getVarsUsedByStmt(stmtNum);
}

std::set<int> UsesReaderImpl::getStmtsRelatedToVar(const std::string& varName) {
  return uses_storage_.getStmtsUsingVar(varName);
}

std::unordered_set<std::string> UsesReaderImpl::getVarsRelatedToProc(
    const string& proc) {
  return uses_storage_.getVarsUsedByProc(proc);
}

std::unordered_set<std::string> UsesReaderImpl::getProcsRelatedToVar(
    const string& varName) {
  return uses_storage_.getProcsUsingVar(varName);
}
