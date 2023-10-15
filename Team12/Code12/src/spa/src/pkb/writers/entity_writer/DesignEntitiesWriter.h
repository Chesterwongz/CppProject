#pragma once

#include <string>

#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/writers/IDesignEntitiesWriter.h"
#include "pkb/interfaces/writers/IStatementWriter.h"
#include "pkb/storage/StmtStore.h"

class DesignEntitiesWriter : public IDesignEntitiesWriter,
                             public IStatementWriter {
 private:
  IEntityStorage& entityStorage;
  StmtStore& stmtStore;

 protected:
  DesignEntitiesWriter(IEntityStorage& entityStorage, StmtStore& stmtStore)
      : entityStorage(entityStorage), stmtStore(stmtStore) {}

 public:
  void addVariable(const std::string& varName) override;
  void addConstant(const std::string& constantValue) override;
  void addProcForStmt(const std::string& procName, int stmtNum) override;
  void addStmt(int stmtNum, StmtType stmtType) override;
};
