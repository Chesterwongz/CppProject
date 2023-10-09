#include "StmtOrProcToVarRelationStorage.h"

void StmtOrProcToVarRelationStorage::setRelatedVar(
    const std::string& variableName, int statementNumber) {
  variableToStatements[variableName].insert(statementNumber);
  statementToVariables[statementNumber].insert(variableName);
}

std::set<int> StmtOrProcToVarRelationStorage::getStmtNumForVar(
    const std::string& variableName) {
  if (variableToStatements.find(variableName) == variableToStatements.end()) {
    return {};
  }
  return variableToStatements[variableName];
}

std::set<std::string> StmtOrProcToVarRelationStorage::getVarForStmt(
    int statementNumber) {
  if (statementToVariables.find(statementNumber) ==
      statementToVariables.end()) {
    return {};
  }
  return statementToVariables[statementNumber];
}

std::set<std::string> StmtOrProcToVarRelationStorage::getAllVarOfStmts() {
  std::set<std::string> allVariables;
  for (const auto& entry : variableToStatements) {
    allVariables.insert(entry.first);
  }
  return allVariables;
}

std::set<int> StmtOrProcToVarRelationStorage::getAllStmtsOfVar() {
  std::set<int> allStatements;
  for (const auto& entry : statementToVariables) {
    allStatements.insert(entry.first);
  }
  return allStatements;
}
