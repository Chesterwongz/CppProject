#pragma once

#include <set>
#include <string>
#include "StmtOrProcToVarReaderTemplate.h"
#include "pkb/interfaces/storage/relation_storage/IModifiesStorage.h"

class ModifiesReaderImpl : public StmtOrProcToVarReaderTemplate {
 private:
  IModifiesStorage& modifies_storage_;

 protected:
  std::set<std::string> getVarsRelatedToStmt(int stmtNum) override;
  std::set<int> getStmtsRelatedToVar(const std::string& varName) override;

 public:
  explicit ModifiesReaderImpl(IModifiesStorage& uses_storage,
                              IStmtStorage& stmt_storage,
                              IEntityStorage& entity_storage)
      : modifies_storage_(uses_storage),
        StmtOrProcToVarReaderTemplate(stmt_storage, entity_storage) {}
};
