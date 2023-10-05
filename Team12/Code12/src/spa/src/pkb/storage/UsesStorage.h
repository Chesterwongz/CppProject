#pragma once

#include <set>
#include <string>
#include <unordered_map>

class UsesStorage {
 public:
  UsesStorage();

  // Setter for uses relationship
  void setVariableUsage(const std::string& variableName, int statementNumber);

  // Return all statement numbers that use a particular variable
  std::set<int> getStatementNumbersForVariable(const std::string& variableName);

  // Return all variable names that are being used in a particular statement
  std::set<std::string> getVariablesForStatement(int statementNumber);

  // Return all variables that are being used in the program
  std::set<std::string> getAllVariables();

  // Return all statements that use a variable in the program
  std::set<int> getAllStatements();

 private:
  // (variable -> statement numbers)
  std::unordered_map<std::string, std::set<int>> variableToStatements;

  // (statement number -> variable names)
  std::unordered_map<int, std::set<std::string>> statementToVariables;
};
