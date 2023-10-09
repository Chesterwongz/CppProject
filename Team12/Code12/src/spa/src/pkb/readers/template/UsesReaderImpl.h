#pragma once

#include <set>
#include <string>
#include "StmtOrProcToVarReaderTemplate.h"
#include "pkb/interfaces/storage/relation_storage/IUsesStorage.h"

class UsesReaderImpl : public StmtOrProcToVarReaderTemplate {
 private:
  IUsesStorage& uses_storage_;

 protected:
  std::set<std::string> getVarsRelatedToStmt(int stmtNum) override;
  std::set<int> getStmtsRelatedToVar(const std::string& varName) override;

 public:
  explicit UsesReaderImpl(IUsesStorage& uses_storage,
                          IStmtStorage& stmt_storage,
                          IEntityStorage& entity_storage)
      : uses_storage_(uses_storage),
        StmtOrProcToVarReaderTemplate(stmt_storage, entity_storage) {}
};
