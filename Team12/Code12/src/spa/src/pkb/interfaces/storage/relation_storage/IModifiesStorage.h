#pragma once

#include <set>
#include <string>

class IModifiesStorage {
 public:
  virtual ~IModifiesStorage() = default;

  // Setter for modifies relationship
  virtual void addModifies(const std::string& varName,
                                       int stmtNum) = 0;

  // Return all variables that are being modified by the particular statement
  virtual std::set<std::string> getVarsModifiedByStmt(
      int stmtNum) = 0;

  // Return all statements that modify the particular variable
  virtual std::set<int> getStmtsModifyingVar(
      const std::string& varName) = 0;
};
