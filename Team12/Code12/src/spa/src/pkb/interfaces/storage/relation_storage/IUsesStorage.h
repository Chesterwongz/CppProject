#pragma once

#include <set>
#include <string>
#include <unordered_set>

class IUsesStorage {
 public:
  virtual ~IUsesStorage() = default;

  // Setter for uses relationship
  virtual void addUses(const std::string& variableName,
                       int statementNumber) = 0;

  virtual void addUses(const std::string& variableName,
                       const std::string& procName) = 0;

  // Return all variable names that are being used in a particular statement
  virtual std::set<std::string> getVarsUsedByStmt(int statementNumber) = 0;

  virtual std::unordered_set<std::string> getVarsUsedByProc(
      const std::string& procName) = 0;

  // Return all statement numbers that use a particular variable
  virtual std::set<int> getStmtsUsingVar(const std::string& variableName) = 0;

  // Return all procedure names that use a particular variable
  virtual std::unordered_set<std::string> getProcsUsingVar(
      const std::string& variableName) = 0;
};
