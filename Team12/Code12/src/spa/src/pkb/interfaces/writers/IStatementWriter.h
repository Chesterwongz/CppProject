#pragma once

#include <string>

class IStatementWriter {
 public:
  virtual ~IStatementWriter() = default;
  virtual void setStatement(int statementNumber, StmtType statementType) = 0;
};
