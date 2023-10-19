#pragma once

#include <set>
#include <string>

#include "common/StmtTypes.h"

class IDesignEntitiesReader {
 public:
  virtual ~IDesignEntitiesReader() = default;

  // return the names of all variables in the program
  virtual std::set<std::string> getAllVariables() = 0;

  virtual vector<string> getVariableName(string varName, StmtType stmtType) = 0;

  virtual bool isValidVariable(string varName) = 0;

  // return the values of all constants in the program
  virtual std::set<std::string> getAllConstants() = 0;

  virtual bool isValidConstant(string constantVal) = 0;

  // return the names of all procedures in the program
  virtual std::set<std::string> getAllProcedures() = 0;

  virtual bool isValidProcName(string procName) = 0;

  // return all the stmts of given type in the program
  virtual std::set<std::string> getStatement(StmtType statementType) = 0;

  virtual bool isValidStatement(string stmtNum,
                                                StmtType statementType) = 0;

  virtual std::string getProcCalledByStmt(int stmtNum) = 0;

  // returns all the stmtnums that call procname
  virtual vector<std::string> getStmtsThatCall(string procName) = 0;

  // returns all the stmtnums that read procname
  virtual vector<std::string> getStmtsThatRead(string varName) = 0;

  // returns the variable that read stmtNum
  virtual string getVariableReadBy(int stmtNum) = 0;

  // returns the variable that read stmtNum
  virtual vector<std::string> getStmtsThatPrint(string varName) = 0;

  virtual string getVariablePrintedBy(int stmtNum) = 0;
  
};
