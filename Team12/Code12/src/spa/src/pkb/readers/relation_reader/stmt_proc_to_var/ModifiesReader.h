#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/utils/CollectionUtils.h"
#include "pkb/interfaces/readers/IModifiesReader.h"
#include "pkb/storage/ModifiesPStore.h"
#include "pkb/storage/ModifiesSStore.h"
#include "pkb/storage/StmtStore.h"

using std::unordered_set, std::string;

class ModifiesReader : public IModifiesReader {
 private:
  ModifiesSStore& modifiesSStore;
  ModifiesPStore& modifiesPStore;
  StmtStore& stmtStore;

 protected:
  explicit ModifiesReader(ModifiesSStore& modifiesStore,
                          ModifiesPStore& modifiesPStore, StmtStore& stmtStore)
      : modifiesSStore(modifiesStore),
        modifiesPStore(modifiesPStore),
        stmtStore(stmtStore) {}

 public:
  std::vector<std::string> getVariablesModifiedBy(int stmtNum) override;

  std::vector<std::string> getStatementsModifying(const std::string& varName,
                                                  StmtType stmtType) override;

  bool isVariableModifiedBy(int stmtNum, const std::string& varName) override;

  std::vector<std::pair<std::string, std::string>> getModifiesStmtPairs(
      StmtType stmtType) override;

  std::vector<std::string> getVarsModifiedByProc(
      const std::string& procName) override;

  std::vector<std::string> getProcModifying(
      const std::string& varName) override;

  bool isVariableModifiedByProc(const std::string& procName,
                                const std::string& varName) override;

  std::vector<std::pair<std::string, std::string>> getModifiesProcPairs()
      override;
};
