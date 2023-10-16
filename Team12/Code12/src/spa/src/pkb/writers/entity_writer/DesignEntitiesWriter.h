#pragma once

#include <string>

#include "common/StmtTypes.h"
#include "pkb/interfaces/writers/IDesignEntitiesWriter.h"
#include "pkb/interfaces/writers/IStatementWriter.h"
#include "pkb/storage/EntityStore.h"
#include "pkb/storage/StmtStore.h"

class DesignEntitiesWriter : public IDesignEntitiesWriter,
                             public IStatementWriter {
 private:
  EntityStore& entityStore;
  StmtStore& stmtStore;

 protected:
  DesignEntitiesWriter(EntityStore& entityStore, StmtStore& stmtStore)
      : entityStore(entityStore), stmtStore(stmtStore) {}

 public:
  void addVar(const std::string& varName) override;
  void addConst(const std::string& constValue) override;
  void addProc(const std::string& procName) override;
  void addStmt(int stmtNum, StmtType stmtType) override;
};
