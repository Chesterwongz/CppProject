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
  virtual void setProcForStmt(const std::string& procedureName,
                              int startStatement) = 0;

  // Return the names of all variables in the program
  virtual std::set<std::string> getAllVariables() = 0;

  // Return all constants in the program
  virtual std::set<std::string> getAllConstants() = 0;

  // Return the names of all procedures in the program
  virtual std::set<std::string> getAllProcedures() = 0;

  /**
   * @param stmtNum Statement number to query.
   * @return Procedure name that the statement belongs to.
   */
  virtual std::string getProcFromStmt(int stmtNum) = 0;
};
