#pragma once

#include <string>
#include <utility>
#include <vector>

class IPatternReader {
 public:
  virtual ~IPatternReader() = default;

  // return list of statement numbers which match the given pattern exactly
  virtual std::vector<std::pair<std::string, std::string>>
  getExactAssignPattern(const std::string& variableName,
                        const std::string& rpn) = 0;

  // return list of statement numbers which match the given pattern partially
  virtual std::vector<std::pair<std::string, std::string>>
  getPartialAssignPattern(const std::string& variableName,
                          const std::string& rpn) = 0;

  // Return all pairs (stmtNum, variableName) where variableName is a variable
  // present in the condition of a while statement at stmtNum
  virtual std::vector<std::pair<std::string, std::string>> getWhilePattern(
      const std::string& variableName) = 0;

  // Return all pairs (stmtNum, variableName) where variableName is a variable
  // present in the condition of an if statement at stmtNum
  virtual std::vector<std::pair<std::string, std::string>> getIfPattern(
      const std::string& variableName) = 0;
};
