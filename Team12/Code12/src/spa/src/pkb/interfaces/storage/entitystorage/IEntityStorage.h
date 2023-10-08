#pragma once

#include <set>
#include <string>

class IEntityStorage {
 public:
  virtual ~IEntityStorage() = default;

  // Setter for variables
  virtual void setVariable(const std::string& variableName) = 0;

  // Setter for constants
  virtual void setConstant(const std::string& constantValue) = 0;

  // Setter for procedure names
  virtual void setProcedure(const std::string& procedureName,
                            int startStatement) = 0;

  // Return the names of all variables in the program
  virtual std::set<std::string> getAllVariables() = 0;

  // Return all constants in the program
  virtual std::set<std::string> getAllConstants() = 0;

  // Return the names of all procedures in the program
  virtual std::set<std::string> getAllProcedures() = 0;

  // Return the name of the procedure whose code begins on that particular
  // statement
  virtual std::string getProcedureStartingOnStatement(int statementNumber) = 0;

  // Return the starting statement number of a particular procedure
  virtual int getStartingStatementOfProcedure(
      const std::string& procedureName) = 0;
};