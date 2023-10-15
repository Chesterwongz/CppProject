#pragma once

#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"
#include "pkb/interfaces/writers/IDesignEntitiesWriter.h"

class DesignEntitiesWriter : public IDesignEntitiesWriter {
 private:
  IEntityStorage& entityStorage;
  IStmtStorage& stmtStorage;

 protected:
  DesignEntitiesWriter(IEntityStorage& entityStorage,
                       IStmtStorage& stmtStorage)
      : entityStorage(entityStorage), stmtStorage(stmtStorage) {}

 public:
  void addVariable(const std::string& varName) override = 0;
  void addConstant(const std::string& constantValue) override = 0;
  void addProcForStmt(const std::string& procName, int stmtNum) override = 0;
  void addStmt(int stmtNum, StmtType stmtType) override = 0;
};
