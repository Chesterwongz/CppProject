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

  // return true if statementNumber is a statement of statementType
  virtual bool isValidStmt(int statementNumber, StmtType statementType) = 0;

  // return true if a constant of that value exists
  virtual bool isValidConstant(std::string constantVal) = 0;

  // return true if a procedure of procName exists
  virtual bool isValidProc(std::string procName) = 0;

  // return true if variable of that varName exists
  virtual bool isValidVariable(std::string varName) = 0;

  // return the statement numbers that call a particular procedure
  virtual std::vector<std::string> getStmtsThatCall(
      const std::string& procName) = 0;

  // return name of procedure called at a particular statementNumber
  virtual std::vector<std::string> getProcCalledBy(int statementNumber) = 0;

  // return the statement numbers that read a particular variable
  virtual std::vector<std::string> getStmtsThatRead(
      const std::string& procName) = 0;

  // return name of variable read at a particular statementNumber
  virtual std::vector<std::string> getVariableReadBy(int statementNumber) = 0;

  // return the statement numbers that print a particular variable
  virtual std::vector<std::string> getStmtsThatPrint(
      const std::string& varName) = 0;

  // return name of variable printed at a particular statementNumber
  virtual std::vector<std::string> getVariablePrintedBy(
      int statementNumber) = 0;
};
