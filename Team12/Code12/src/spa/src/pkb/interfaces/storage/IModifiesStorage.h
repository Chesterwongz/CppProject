#pragma once

#include <set>
#include <string>

class IModifiesStorage {
 public:
  virtual ~IModifiesStorage() = default;

  virtual void setVariableModification(const std::string& variableName,
                                       int statementNumber) = 0;

  virtual std::set<std::string> getModifiedVariablesForStatement(
      int statementNumber) = 0;

  virtual std::set<int> getStatementNumbersForModifiedVariable(
      const std::string& variableName) = 0;
};
