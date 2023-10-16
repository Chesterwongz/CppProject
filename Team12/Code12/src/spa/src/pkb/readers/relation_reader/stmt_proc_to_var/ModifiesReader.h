#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/interfaces/readers/IModifiesReader.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"
#include "pkb/interfaces/storage/relation_storage/IModifiesStorage.h"
#include "pkb/readers/relation_reader/stmt_proc_to_var/impl/ModifiesReaderImpl.h"
#include "pkb/storage/ModifiesPStore.h"
#include "pkb/storage/ModifiesStore.h"
#include "pkb/storage/StmtStore.h"

using std::unordered_set, std::string;

class ModifiesReader : public IModifiesReader {
 private:
  ModifiesStore& modifiesStore;
  ModifiesPStore& modifiesPStore;
  StmtStore& stmtStore;

 protected:
  explicit ModifiesReader(ModifiesStore& modifiesStore,
                          ModifiesPStore& modifiesPStore, StmtStore& stmtStore)
      : modifiesStore(modifiesStore),
        modifiesPStore(modifiesPStore),
        stmtStore(stmtStore) {}

 public:
  std::vector<std::string> getVariablesModifiedBy(int stmtNum) override;

  std::vector<std::string> getStatementsModifying(const std::string& varName,
                                                  StmtType stmtType) override;

  bool isVariableModifiedBy(int stmtNum, const std::string& varName) override;

  std::vector<std::pair<std::string, std::string>> getModifiesPairs(
      StmtType stmtType) override;

  unordered_set<string> getModifiedVariablesForProc(
      const string& procName) override;
};
