#pragma once

#include <set>
#include <string>
#include <unordered_map>

class ModifiesStorage {
 public:
  ModifiesStorage();

  // Setter for modifies relationship
  void setVariableModification(const std::string& variableName,
                               int statementNumber);

  // Return all statements that modify the particular variable
  std::set<int> getStatementNumbersForVariable(const std::string& variableName);

  // Return all variables that are being modified by the particular statement
  std::set<std::string> getVariablesForStatement(int statementNumber);

  // Return all variables that are being modified in the program
  std::set<std::string> getAllVariables();

  // Return all statements that modify a variable in the program
  std::set<int> getAllStatements();

 private:
  // (variable -> statement numbers)
  std::unordered_map<std::string, std::set<int>> variableToStatements;

  // (statement number -> variable names)
  std::unordered_map<int, std::set<std::string>> statementToVariables;
};