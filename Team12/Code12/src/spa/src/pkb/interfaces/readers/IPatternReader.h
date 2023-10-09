#pragma once

#include <string>
#include <vector>

class IPatternReader {
 public:
  virtual ~IPatternReader() = default;

  // return list of statement numbers which match the given pattern exactly
  virtual std::vector<std::string> getExactAssignPattern(
      const std::string& variableName, const std::string& rpn,
      bool isSynonym) = 0;

  // return list of statement numbers which match the given pattern partially
  virtual std::vector<std::string> getPartialAssignPattern(
      const std::string& variableName, const std::string& rpn,
      bool isSynonym) = 0;
};
