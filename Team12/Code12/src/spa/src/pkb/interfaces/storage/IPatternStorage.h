#pragma once

#include <set>
#include <string>
#include <vector>

class IPatternStorage {
 public:
  virtual ~IPatternStorage() = default;

  virtual void setAssignPattern(const std::string& variableName,
                                const std::string& rpn,
                                int statementNumber) = 0;

  virtual std::vector<std::string> getExactAssignPattern(
      const std::string& variableName, const std::string& rpn,
      bool isSynonym) = 0;
  virtual std::vector<std::string> getPartialAssignPattern(
      const std::string& variableName, const std::string& rpn,
      bool isSynonym) = 0;
};