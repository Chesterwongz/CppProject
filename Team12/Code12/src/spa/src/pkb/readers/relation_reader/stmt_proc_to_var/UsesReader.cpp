#include "UsesReader.h"

// (1, v)
std::vector<std::string> UsesReader::getVariablesUsedBy(int stmt) {
  return reader.getVarByStmt(stmt);
}

// (s, "name")
std::vector<std::string> UsesReader::getStatementsUsing(
    const std::string& varName, StmtType stmtType) {
  return reader.getStmtByVar(varName, stmtType);
}

bool UsesReader::isVariableUsedBy(int stmt, const std::string& varName) {
  return reader.hasDirectRelation(stmt, varName);
}

std::vector<std::pair<std::string, std::string>> UsesReader::getUsesStmtPairs(
    StmtType stmtType1) {
  return reader.getStmtVarPairs(stmtType1);
}

// =================================== UsesP ===================================

std::vector<std::string> UsesReader::getVarsUsedByProc(
    const std::string& procName) {
  return reader.getVarByProc(procName);
}

std::vector<std::string> UsesReader::getProcUsing(const std::string& varName) {
  return reader.getProcByVar(varName);
}

bool UsesReader::isVariableUsedByProc(const std::string& procName,
                                      const std::string& varName) {
  return reader.hasDirectRelation(procName, varName);
}

std::vector<std::pair<std::string, std::string>>
UsesReader::getUsesProcPairs() {
  return reader.getProcVarPairs();
}
