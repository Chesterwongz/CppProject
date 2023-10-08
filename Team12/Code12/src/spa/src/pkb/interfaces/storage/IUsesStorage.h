#pragma once

#include <set>
#include <string>

class IUsesStorage {
 public:
  virtual ~IUsesStorage() = default;

  virtual void setVariableUsage(const std::string& variableName,
                                int statementNumber) = 0;

  virtual std::set<std::string> getUsedVariablesForStatement(
      int statementNumber) = 0;

  virtual std::set<int> getStatementNumbersForUsedVariable(
      const std::string& variableName) = 0;
};