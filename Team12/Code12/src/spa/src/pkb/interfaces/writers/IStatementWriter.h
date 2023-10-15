#pragma once

#include <string>

class IStatementWriter {
 public:
  virtual ~IStatementWriter() = default;
  virtual void addStmt(int stmtNum, StmtType stmtType) = 0;
};
