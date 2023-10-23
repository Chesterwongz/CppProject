#pragma once

#include <string>

#include "common/StmtTypes.h"

class IDesignEntitiesWriter {
 public:
  virtual ~IDesignEntitiesWriter() = default;
  virtual void addVar(const std::string& varName) = 0;
  virtual void addConst(const std::string& constValue) = 0;
  virtual void addProc(const std::string& procName) = 0;
  virtual void addStmt(int stmtNum, StmtType stmtType) = 0;
};
