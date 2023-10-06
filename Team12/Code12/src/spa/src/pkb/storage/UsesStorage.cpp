#include "UsesStorage.h"

UsesStorage::UsesStorage() {}

void UsesStorage::setVariableUsage(const std::string& variableName,
                                   int statementNumber) {
  variableToStatements[variableName].insert(statementNumber);
  statementToVariables[statementNumber].insert(variableName);
}

void UsesStorage::setVariableUsage(const std::string& variableName,
                                   const std::string& procName) {
  variableToProc[variableName].insert(procName);
  procToVariables[procName].insert(variableName);
}

std::set<int> UsesStorage::getStatementNumbersForVariable(
    const std::string& variableName) {
  if (variableToStatements.find(variableName) == variableToStatements.end()) {
    return {};
  }
  return variableToStatements[variableName];
}

std::set<std::string> UsesStorage::getVariablesForStatement(
    int statementNumber) {
  if (statementToVariables.find(statementNumber) ==
      statementToVariables.end()) {
    return {};
  }
  return statementToVariables[statementNumber];
}

std::unordered_set<std::string> UsesStorage::getVariablesForProc(
    const std::string& procName) {
  if (procToVariables.find(procName) == procToVariables.end()) {
    return {};
  }
  return procToVariables[procName];
}

std::set<std::string> UsesStorage::getAllVariables() {
  std::set<std::string> allVariables;
  for (const auto& entry : variableToStatements) {
    allVariables.insert(entry.first);
  }
  return allVariables;
}

std::set<int> UsesStorage::getAllStatements() {
  std::set<int> allStatements;
  for (const auto& entry : statementToVariables) {
    allStatements.insert(entry.first);
  }
  return allStatements;
}
