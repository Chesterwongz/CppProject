#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/utils/CollectionUtils.h"
#include "pkb/interfaces/readers/IUsesReader.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/relation_storage/RelationStore.h"

class UsesReader : public IUsesReader {
 private:
  RelationStore<int, std::string>& usesSStore;
  RelationStore<std::string, std::string>& usesPStore;
  StmtStore& stmtStore;

 protected:
  explicit UsesReader(RelationStore<int, std::string>& usesStore,
                      RelationStore<std::string, std::string>& usesPStore,
                      StmtStore& stmtStore)
      : usesSStore(usesStore), usesPStore(usesPStore), stmtStore(stmtStore) {}

 public:
  std::vector<std::string> getVariablesUsedBy(int stmt) override;

  std::vector<std::string> getStatementsUsing(const std::string& varName,
                                              StmtType stmtType) override;

  bool isVariableUsedBy(int stmt, const std::string& varName) override;

  std::vector<std::pair<std::string, std::string>> getUsesStmtPairs(
      StmtType stmtType1) override;

  std::vector<std::string> getVarsUsedByProc(
      const std::string& procName) override;

  std::vector<std::string> getProcUsing(const std::string& varName) override;

  bool isVariableUsedByProc(const std::string& procName,
                            const std::string& varName) override;

  std::vector<std::pair<std::string, std::string>> getUsesProcPairs() override;
};
