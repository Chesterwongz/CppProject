#pragma once

#include <set>
#include <string>
#include <unordered_set>

class IModifiesStorage {
 public:
  virtual ~IModifiesStorage() = default;

  // Setter for modifies relationship
  virtual void addModifies(const std::string& varName, int stmtNum) = 0;

  virtual void addModifies(const std::string& varName,
                           const std::string& procName) = 0;

  // Return all variables that are being modified by the particular statement
  virtual std::set<std::string> getVarsModifiedByStmt(int stmtNum) = 0;

  virtual std::unordered_set<std::string> getVarsModifiedByProc(
      const std::string& procName) = 0;

  // Return all statements that modifies the particular variable
  virtual std::set<int> getStmtsModifyingVar(const std::string& varName) = 0;

  // Return all procedure names that modifies a particular variable
  virtual std::unordered_set<std::string> getProcsModifyingVar(
      const std::string& variableName) = 0;
};
