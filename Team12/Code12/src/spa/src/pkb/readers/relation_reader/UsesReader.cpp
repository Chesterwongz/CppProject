#include "UsesReader.h"

std::vector<std::string> UsesReader::getStatementsUsing(
    const std::string& variableName, StmtType statementType) {
  return uses_reader_.getStmtsRelatedToVarByStmtType(variableName,
                                                     statementType);
}

std::vector<std::string> UsesReader::getProcUsing(
    const std::string& variableName) {
  std::unordered_set<std::string> proceduresUsing =
      uses_reader_.getProcsRelatedToVar(variableName);
  std::vector<std::string> proceduresUsingVector(proceduresUsing.begin(),
                                                 proceduresUsing.end());
  return proceduresUsingVector;
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

bool UsesReader::isVariableUsedByProc(const std::string& variableName,
                                      const std::string& procName) {
  return uses_reader_.isVarRelatedToProc(variableName, procName);
}

std::vector<std::pair<std::string, std::string>>
UsesReader::getAllUsedVariables(StmtType statementType) {
  return uses_reader_.getAllRelationsByStmtType(statementType);
}

std::vector<std::string> UsesReader::getVarsUsedByProc(
    const std::string& procName) {
  std::unordered_set<std::string> variablesUsed =
      uses_reader_.getVarsRelatedToProc(procName);
  std::vector<std::string> variablesUsedVector(variablesUsed.begin(),
                                               variablesUsed.end());
  return variablesUsedVector;
}

std::vector<std::pair<std::string, std::string>>
UsesReader::getUsesProcPairs() {
  return uses_reader_.getAllProcRelations();
}
