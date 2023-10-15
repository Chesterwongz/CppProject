#pragma once

#include <string>

#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"
#include "pkb/interfaces/writers/IDesignEntitiesWriter.h"
#include "pkb/interfaces/writers/IStatementWriter.h"

class DesignEntitiesWriter : public IDesignEntitiesWriter,
                             public IStatementWriter {
 private:
  IEntityStorage& entityStorage;
  IStmtStorage& stmtStorage;

 protected:
  DesignEntitiesWriter(IEntityStorage& entityStorage, IStmtStorage& stmtStorage)
      : entityStorage(entityStorage), stmtStorage(stmtStorage) {}

 public:
  void addVariable(const std::string& varName) override;
  void addConstant(const std::string& constantValue) override;
  void addProcForStmt(const std::string& procName, int stmtNum) override;
  void addStmt(int stmtNum, StmtType stmtType) override;
};
