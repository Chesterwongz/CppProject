#include "ModifiesReader.h"

std::vector<std::string> ModifiesReader::getStatementsModifying(
    const std::string& variableName, StmtType statementType) {
  return modifies_reader_.getStmtsRelatedToVarByStmtType(variableName,
                                                         statementType);
}

std::vector<std::string> ModifiesReader::getProcModifying(
    const std::string& varName) {
  std::unordered_set<std::string> modifyingProcedures =
      modifies_reader_.getProcsRelatedToVar(varName);
  std::vector<std::string> modifyingProceduresVector(
      modifyingProcedures.begin(), modifyingProcedures.end());
  return modifyingProceduresVector;
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

bool ModifiesReader::isVariableModifiedByProc(const string& procName,
                                              const string& varName) {
  return modifies_reader_.isVarRelatedToProc(varName, procName);
}

std::vector<std::pair<std::string, std::string>>
ModifiesReader::getAllModifiedVariables(StmtType statementType) {
  return modifies_reader_.getAllRelationsByStmtType(statementType);
}

std::vector<std::string> ModifiesReader::getVarsModifiedByProc(
    const string& procName) {
  std::unordered_set<std::string> modifiedVariables =
      modifies_reader_.getVarsRelatedToProc(procName);
  std::vector<std::string> modifiedVariablesVector(modifiedVariables.begin(),
                                                   modifiedVariables.end());
  return modifiedVariablesVector;
}

std::vector<std::pair<std::string, std::string>>
ModifiesReader::getModifiesProcPairs() {
  return modifies_reader_.getAllProcRelations();
}
