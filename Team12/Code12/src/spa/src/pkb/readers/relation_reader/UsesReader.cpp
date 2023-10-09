#include "UsesReader.h"

std::vector<std::string> UsesReader::getStatementsUsing(
    const std::string& variableName, StmtType statementType) {
  return uses_reader_.getStmtsRelatedToVarByStmtType(variableName,
                                                     statementType);
}

std::vector<std::pair<std::string, std::string>> UsesReader::getVariablesUsedBy(
    int statementNumber, StmtType statementType) {
  return uses_reader_.getVarsRelatedToStmtByStmtType(statementNumber,
                                                     statementType);
}

bool UsesReader::isVariableUsedBy(const std::string& variableName,
                                  const std::string& statementNumber) {
  return uses_reader_.isVarRelatedToStmt(variableName, statementNumber);
}

std::vector<std::pair<std::string, std::string>>
UsesReader::getAllUsedVariables(StmtType statementType) {
  return uses_reader_.getAllRelationsByStmtType(statementType);
}

std::unordered_set<std::string> UsesReader::getUsedVariablesForProc(
    const std::string& procName) {
  return uses_reader_.getVarsRelatedToProc(procName);
}
