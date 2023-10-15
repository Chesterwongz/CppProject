#pragma once

#include <string>

class IDesignEntitiesWriter {
 public:
  virtual ~IDesignEntitiesWriter() = default;
  virtual void addVariable(const std::string& varName) = 0;
  virtual void addConstant(const std::string& constantValue) = 0;
  virtual void addProcForStmt(const std::string& procName,
                              int stmtNum) = 0;
  virtual void addStmt(int stmtNum, StmtType stmtType) = 0;
};
