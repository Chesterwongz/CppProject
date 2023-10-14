#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/utils/CollectionUtils.h"
#include "pkb/interfaces/readers/IUsesReader.h"
#include "pkb/storage/StmtStore.h"
#include "pkb/storage/UsesPStore.h"
#include "pkb/storage/UsesStore.h"

class UsesReader : public IUsesReader {
 private:
  UsesStore& usesStore;
  UsesPStore& usesPStore;
  StmtStore& stmtStore;

 protected:
  explicit UsesReader(UsesStore& usesStore, UsesPStore& usesPStore,
                      StmtStore& stmtStore)
      : usesStore(usesStore), usesPStore(usesPStore), stmtStore(stmtStore) {}

 public:
  std::vector<std::string> getVariablesUsedBy(int stmt) override;

  std::vector<std::string> getStatementsUsing(const std::string& varName,
                                              StmtType stmtType) override;

  bool isVariableUsedBy(int stmt, const std::string& varName) override;

  std::vector<std::pair<std::string, std::string>> getUsesPairs(
      StmtType stmtType) override;

  std::unordered_set<std::string> getUsedVariablesForProc(
      const std::string& procName) override;
};
