#pragma once

#include <string>

class IPatternWriter {
 public:
  virtual ~IPatternWriter() = default;
  virtual void setAssignPattern(const std::string& variableName,
                                const std::string& rpn,
                                int statementNumber) = 0;

  virtual void setWhilePattern(int statementNumber,
                               const std::string& variableName) = 0;
  virtual void setIfPattern(int statementNumber,
                            const std::string& variableName) = 0;
};
