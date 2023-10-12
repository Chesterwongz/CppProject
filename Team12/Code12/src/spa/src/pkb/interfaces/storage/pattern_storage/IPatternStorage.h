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

  virtual void setWhilePattern(int statementNumber,
                               const std::string& variableName) = 0;

  virtual void setIfPattern(int statementNumber,
                            const std::string& variableName) = 0;

  virtual std::vector<std::pair<std::string, std::string>>
  getExactAssignPattern(const std::string& variableName,
                        const std::string& rpn) = 0;
  virtual std::vector<std::pair<std::string, std::string>>
  getPartialAssignPattern(const std::string& variableName,
                          const std::string& rpn) = 0;

  virtual std::vector<std::pair<std::string, std::string>> getWhilePattern(
      const std::string& variableName) = 0;

  virtual std::vector<std::pair<std::string, std::string>> getIfPattern(
      const std::string& variableName) = 0;
};
