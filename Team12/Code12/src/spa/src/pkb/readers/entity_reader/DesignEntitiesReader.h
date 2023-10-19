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

  bool isValidStmt(int statementNumber, StmtType statementType) override;

  bool isValidConstant(std::string constantVal) override;

  bool isValidProc(std::string procName) override;

  bool isValidVariable(std::string varName) override;

  std::vector<std::string> getStmtsThatCall(
      const std::string& procName) override;

  std::string getProcCalledBy(int statementNumber) override;

  std::vector<std::string> getStmtsThatRead(
      const std::string& varName) override;

  std::string getVariableReadBy(int statementNumber) override;

  std::vector<std::string> getStmtsThatPrint(
      const std::string& varName) override;

  std::string getVariablePrintedBy(int statementNumber) override;

  template<typename SStoreType>
  std::string getEntityBy(int statementNumber, StmtType stmtType, SStoreType& sStore);
};
