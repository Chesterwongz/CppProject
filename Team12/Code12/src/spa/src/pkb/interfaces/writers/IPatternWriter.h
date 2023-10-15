#pragma once

#include <string>

class IPatternWriter {
 public:
  virtual ~IPatternWriter() = default;
  virtual void addAssignPattern(const std::string& varName,
                                const std::string& rpn, int stmtNum) = 0;

  virtual void addWhilePattern(int stmtNum, const std::string& varName) = 0;
  virtual void addIfPattern(int stmtNum, const std::string& varName) = 0;
};
