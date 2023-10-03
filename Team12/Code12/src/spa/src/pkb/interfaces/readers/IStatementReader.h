#pragma once
#include <set>

#include "common/StmtTypes.h"

class IStatementReader {
 public:
  virtual std::set<std::string> getStatement(StmtType statementType) = 0;
  virtual std::vector<std::string> getExactAssignPattern(
      const std::string& variableName, const std::string& rpn,
      bool isSynonym) = 0;
  virtual std::vector<std::string> getPartialAssignPattern(
      const std::string& variableName, const std::string& rpn,
      bool isSynonym) = 0;
};
