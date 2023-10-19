#pragma once

#include <string>
#include <vector>

#include "common/StmtTypes.h"

class IDesignEntitiesReader {
 public:
  virtual ~IDesignEntitiesReader() = default;

  // return the names of all variables in the program
  virtual std::vector<std::string> getAllVariables() = 0;

  // return the values of all constants in the program
  virtual std::vector<std::string> getAllConstants() = 0;

  // return the names of all procedures in the program
  virtual std::vector<std::string> getAllProcedures() = 0;

  // return all the stmts of given type in the program
  virtual std::vector<std::string> getAllStmtsOf(StmtType statementType) = 0;

  virtual bool isValidStmt(int statementNumber, StmtType statementType) = 0;

  virtual bool isValidConstant(std::string constantVal) = 0;

  virtual bool isValidProc(std::string procName) = 0;

  virtual bool isValidVariable(std::string varName) = 0;

  virtual std::vector<std::string> getStmtsThatCall(
      const std::string& procName) = 0;

  virtual std::string getProcCalledBy(int statementNumber) = 0;

  virtual std::vector<std::string> getStmtsThatRead(
      const std::string& procName) = 0;

  virtual std::string getVariableReadBy(int statementNumber) = 0;

  virtual std::vector<std::string> getStmtsThatPrint(
      const std::string& varName) = 0;

  virtual std::string getVariablePrintedBy(int statementNumber) = 0;
};
