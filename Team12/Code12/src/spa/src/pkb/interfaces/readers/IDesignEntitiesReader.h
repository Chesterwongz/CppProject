#pragma once

#include <set>
#include <string>
#include <vector>

#include "common/StmtTypes.h"

using std::vector, std::string;

class IDesignEntitiesReader {
 public:
  virtual ~IDesignEntitiesReader() = default;

  // return the names of all variables in the program
  virtual std::set<std::string> getAllVariables() = 0;

  // virtual bool isValidVariable(string varName);

  // return the values of all constants in the program
  virtual std::set<std::string> getAllConstants() = 0;

  // virtual bool isValidConstant(int constantVal);

  // return the names of all procedures in the program
  virtual std::set<std::string> getAllProcedures() = 0;

  // virtual bool isValidProcName(string procName);

  // return all the stmts of given type in the program
  virtual std::set<std::string> getStatement(StmtType statementType) = 0;

  // virtual bool isValidStatement(string stmtNum,
  //                                              StmtType statementType);

  // virtual std::string getProcCalledByStmt(int stmtNum);

  // returns all the stmtnums that call procname
  // virtual vector<std::string> getStmtsThatCall(string procName);

  // returns all the stmtnums that read procname
  // virtual vector<std::string> getStmtsThatRead(string varName);

  // returns the variable that read stmtNum
  // virtual string getVariableReadBy(int stmtNum);

  // returns the variable that read stmtNum
  // virtual vector<std::string> getStmtsThatPrint(string varName);

  // virtual string getVariablePrintedBy(int stmtNum);
  
  virtual std::string getProcFromStmt(int stmtNum) = 0;
};
