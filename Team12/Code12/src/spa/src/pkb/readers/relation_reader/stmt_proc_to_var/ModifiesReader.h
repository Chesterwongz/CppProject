#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "StmtOrProcToVarReader.h"
#include "pkb/interfaces/readers/IModifiesReader.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/relation_storage/RelationStore.h"

using std::unordered_set, std::string;

class ModifiesReader : public IModifiesReader {
 private:
  StmtOrProcToVarReader reader;

 protected:
  explicit ModifiesReader(
      RelationStore<int, std::string>& modifiesStore,
      RelationStore<std::string, std::string>& modifiesPStore,
      StmtStore& stmtStore)
      : reader(modifiesStore, modifiesPStore, stmtStore) {}

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
