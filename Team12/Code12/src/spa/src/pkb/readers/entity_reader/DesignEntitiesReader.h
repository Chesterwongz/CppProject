#pragma once

#include <set>
#include <string>

#include "pkb/interfaces/readers/IDesignEntitiesReader.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"

class DesignEntitiesReader : public IDesignEntitiesReader {
 private:
  IEntityStorage& entity_storage_;
  IStmtStorage& stmt_storage_;

 protected:
  DesignEntitiesReader(IEntityStorage& entity_storage,
                       IStmtStorage& stmt_storage)
      : entity_storage_(entity_storage), stmt_storage_(stmt_storage) {}

 public:
  // return the names of all variables in the program
  std::set<std::string> getAllVariables() override;

  // return {varName} if exists, {} otherwise
  vector<string> getVariableName(string varName, StmtType stmtType) override;

  // return {varName} if exists, {} otherwise
  bool isValidVariable(string varName) override;

  // return the values of all constants in the program
  std::set<std::string> getAllConstants() override;

  // return true if exists, false otherwise
  bool isValidConstant(string constantVal) override;

  // return the names of all procedures in the program
  std::set<std::string> getAllProcedures() override;

  // return true if it exists, false otherwise
  bool isValidProcName(string procName) override;

  // return the statement numbers of specified statement type
  std::set<std::string> getStatement(StmtType statementType) override;

  // return true if it exists, false otherwise
  bool isValidStatement(string stmtNum, StmtType statementType) override;

  std::string getProcCalledByStmt(int stmtNum) override;

  // returns all the stmtnums that call procname
  std::vector<string> getStmtsThatCall(string procName) override;

  vector<std::string> getStmtsThatRead(string varName) override;

  vector<std::string> getStmtsThatPrint(string varName) override;

  string getVariableReadBy(int stmtNum) override;

  string getVariablePrintedBy(int stmtNum) override;

};
