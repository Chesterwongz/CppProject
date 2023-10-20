#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "common/utils/CollectionUtils.h"
#include "common/utils/StringUtils.h"
#include "pkb/interfaces/readers/IDesignEntitiesReader.h"
#include "pkb/storage/CallsSStore.h"
#include "pkb/storage/EntityStore.h"
#include "pkb/storage/ModifiesSStore.h"
#include "pkb/storage/StmtStore.h"
#include "pkb/storage/UsesSStore.h"

class DesignEntitiesReader : public IDesignEntitiesReader {
 private:
  CallsSStore& callsSStore;
  EntityStore& entityStore;
  ModifiesSStore& modifiesSStore;
  StmtStore& stmtStore;
  UsesSStore& usesSStore;

 protected:
  DesignEntitiesReader(CallsSStore& callsSStore, EntityStore& entityStore,
                       ModifiesSStore& modifiesSStore, StmtStore& stmtStore,
                       UsesSStore& usesSStore)
      : callsSStore(callsSStore),
        entityStore(entityStore),
        modifiesSStore(modifiesSStore),
        stmtStore(stmtStore),
        usesSStore(usesSStore) {}

 public:
  // return the names of all variables in the program
  std::vector<std::string> getAllVariables() override;

  // return the values of all constants in the program
  std::vector<std::string> getAllConstants() override;

  // return the names of all procedures in the program
  std::vector<std::string> getAllProcedures() override;

  // return the statement numbers of specified statement type
  std::vector<std::string> getAllStmtsOf(StmtType statementType) override;

  // return true if statementNumber is a statement of statementType
  bool isValidStmt(int statementNumber, StmtType statementType) override;

  // return true if a constant of that value exists
  bool isValidConstant(std::string constantVal) override;

  // return true if a procedure of procName exists
  bool isValidProc(std::string procName) override;

  // return true if variable of that varName exists
  bool isValidVariable(std::string varName) override;

  // return the statement numbers that call a particular procedure
  std::vector<std::string> getStmtsThatCall(
      const std::string& procName) override;

  // return name of procedure called at a particular statementNumber
  std::vector<std::string> getProcCalledBy(int statementNumber) override;

  // return the statement numbers that read a particular variable
  std::vector<std::string> getStmtsThatRead(
      const std::string& varName) override;

  // return name of variable read at a particular statementNumber
  std::vector<std::string> getVariableReadBy(int statementNumber) override;

  // return the statement numbers that print a particular variable
  std::vector<std::string> getStmtsThatPrint(
      const std::string& varName) override;

  // return name of variable printed at a particular statementNumber
  std::vector<std::string> getVariablePrintedBy(int statementNumber) override;

  // return all pairs of call statement numbers and the procedures called at
  // those statements
  std::vector<std::pair<std::string, std::string>> getAllStmtProcCallsPairs()
      override;

  // return all pairs of read statement numbers and the variables read at those
  // statements
  std::vector<std::pair<std::string, std::string>> getAllStmtVarReadPairs()
      override;

  // return all pairs of print statement numbers and the variables printed at
  // those statements
  std::vector<std::pair<std::string, std::string>> getAllStmtVarPrintPairs()
      override;

  template <typename SStoreType>
  std::vector<std::string> getEntityBy(int statementNumber, StmtType stmtType,
                                       SStoreType& sStore);
};
