#pragma once

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>

class UsesStorage {
 public:
  UsesStorage();

  // Setter for uses relationship
  void setVariableUsage(const std::string& variableName, int statementNumber);

  void setVariableUsage(const std::string& variableName,
                        const std::string& procName);

  // Return all statement numbers that use a particular variable
  std::set<int> getStatementNumbersForVariable(const std::string& variableName);

  std::unordered_set<std::string> getVariablesForProc(
      const std::string& procName);

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

  // (procedure name -> variable names)
  std::unordered_map<std::string, std::unordered_set<std::string>>
      procToVariables;

  // (variable name -> procedure names)
  std::unordered_map<std::string, std::unordered_set<std::string>>
      variableToProc;
};
