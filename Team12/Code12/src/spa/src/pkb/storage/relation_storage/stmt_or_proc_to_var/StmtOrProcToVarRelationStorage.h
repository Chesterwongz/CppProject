#pragma once

#include <set>
#include <string>
#include <unordered_map>

class StmtOrProcToVarRelationStorage {
 private:
  // (variable -> statement numbers)
  std::unordered_map<std::string, std::set<int>> variableToStatements;

  // (statement number -> variable names)
  std::unordered_map<int, std::set<std::string>> statementToVariables;

 public:
  // Setter for relationship
  void setRelatedVar(const std::string& varName, int stmtNum);

  // Return all statement numbers related to a particular variable
  std::set<int> getStmtNumForVar(const std::string& varName);

  // Return all variable names that are being related to a particular
  // statement
  std::set<std::string> getVarForStmt(int stmtNum);

  // Return all variables that have StmtToVar relations in the program
  std::set<std::string> getAllVarOfStmts();

  // Return all statements that are have a StmtToVarRelation in the program
  std::set<int> getAllStmtsOfVar();
};
