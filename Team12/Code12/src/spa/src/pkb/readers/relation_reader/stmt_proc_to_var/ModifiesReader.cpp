#include "ModifiesReader.h"

// (1, v)
std::vector<std::string> ModifiesReader::getVariablesModifiedBy(int stmt) {
  return reader.getVarByStmt(stmt);
}

// (s, "name")
std::vector<std::string> ModifiesReader::getStatementsModifying(
    const std::string& varName, StmtType stmtType) {
  return reader.getStmtByVar(varName, stmtType);
}

bool ModifiesReader::isVariableModifiedBy(int stmt,
                                          const std::string& varName) {
  return reader.hasDirectRelation(stmt, varName);
}

std::vector<std::pair<std::string, std::string>>
ModifiesReader::getModifiesStmtPairs(StmtType stmtType) {
  return reader.getStmtVarPairs(stmtType);
}

// ================================= ModifiesP =================================

std::vector<std::string> ModifiesReader::getVarsModifiedByProc(
    const string& procName) {
  return reader.getVarByProc(procName);
}

std::vector<std::string> ModifiesReader::getProcModifying(
    const string& varName) {
  return reader.getProcByVar(varName);
}

bool ModifiesReader::isVariableModifiedByProc(const string& procName,
                                              const string& varName) {
  return reader.hasDirectRelation(procName, varName);
}

std::vector<std::pair<std::string, std::string>>
ModifiesReader::getModifiesProcPairs() {
  return reader.getProcVarPairs();
}
