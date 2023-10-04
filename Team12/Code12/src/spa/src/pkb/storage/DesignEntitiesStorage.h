#pragma once

#include <set>
#include <string>
#include <unordered_map>

class DesignEntitiesStorage {
 public:
  DesignEntitiesStorage();

  // Setter for variables
  void setVariable(const std::string& variableName);

  // Setter for constants
  void setConstant(const std::string& constantValue);

  // Setter for procedure names
  void setProcedure(const std::string& procedureName, int startStatement);

  // Return the names of all variables in the program
  std::set<std::string> getAllVariables();

  // Return all constants in the program
  std::set<std::string> getAllConstants();

  // Return the names of all procedures in the program
  std::set<std::string> getAllProcedures();

  // Return the name of the procedure whose code begins on that particular
  // statement
  std::string getProcedureStartingOnStatement(int statementNumber);

  // Return the starting statement number of a particular procedure
  int getStartingStatementOfProcedure(const std::string& procedureName);

 private:
  std::set<std::string> variableData;

  std::set<std::string> constantData;

  // procedure name -> starting statement
  std::unordered_map<std::string, int> procedureData;
};
