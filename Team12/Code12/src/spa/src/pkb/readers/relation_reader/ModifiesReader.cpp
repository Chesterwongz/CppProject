#include "ModifiesReader.h"

std::vector<std::string> ModifiesReader::getStatementsModifying(
    const std::string& variableName, StmtType statementType) {
  return modifies_reader_.getStmtsRelatedToVarByStmtType(variableName,
                                                         statementType);
}

std::unordered_set<std::string> ModifiesReader::getProceduresModifying(
    const string& variableName) {
  return modifies_reader_.getProcsRelatedToVar(variableName);
}

std::vector<std::pair<std::string, std::string>>
ModifiesReader::getVariablesModifiedBy(int statementNumber,
                                       StmtType statementType) {
  return modifies_reader_.getVarsRelatedToStmtByStmtType(statementNumber,
                                                         statementType);
}

bool ModifiesReader::isVariableModifiedBy(const std::string& variableName,
                                          const std::string& statementNumber) {
  return modifies_reader_.isVarRelatedToStmt(variableName, statementNumber);
}

bool ModifiesReader::isVariableModifiedByProc(const string& variableName,
                                              const string& procName) {
  return modifies_reader_.isVarRelatedToProc(variableName, procName);
}

std::vector<std::pair<std::string, std::string>>
ModifiesReader::getAllModifiedVariables(StmtType statementType) {
  return modifies_reader_.getAllRelationsByStmtType(statementType);
}

unordered_set<string> ModifiesReader::getModifiedVariablesForProc(
    const string& procName) {
  return modifies_reader_.getVarsRelatedToProc(procName);
}

std::vector<std::pair<std::string, std::string>>
ModifiesReader::getAllModifiedVariablesByProcs() {
  return modifies_reader_.getAllProcRelations();
}
