#pragma once

#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/Constants.h"
#include "common/utils/CollectionUtils.h"
#include "pkb/interfaces/readers/IAffectsReader.h"
#include "pkb/storage/AffectsCache.h"
#include "pkb/storage/ModifiesSStore.h"
#include "pkb/storage/NextStore.h"
#include "pkb/storage/StmtStore.h"
#include "pkb/storage/UsesSStore.h"

class AffectsReader : public IAffectsReader {
 private:
  AffectsCache& affectsCache;
  ModifiesSStore& modifiesSStore;
  NextStore& nextStore;
  StmtStore& stmtStore;
  UsesSStore& usesSStore;

 public:
  explicit AffectsReader(AffectsCache& affectsCache,
                         ModifiesSStore& modifiesSStore, NextStore& nextStore,
                         StmtStore& stmtStore, UsesSStore& usesSStore)
      : affectsCache(affectsCache),
        modifiesSStore(modifiesSStore),
        nextStore(nextStore),
        stmtStore(stmtStore),
        usesSStore(usesSStore) {}

  std::vector<std::pair<std::string, std::string>> getAffectsPairs() override;

  bool isAffects(int firstStmtNum, int secondStmtNum) override;

  std::vector<std::string> getAffects(int firstStmtNum,
                                      StmtType stmtType) override;
  std::vector<std::string> getAffectedBy(int secondStmtNum,
                                         StmtType stmtType) override;

  void findAffectsPairs(
      int originalStmt, int currentStmt, const std::string& variable,
      std::unordered_set<std::string>& done,
      std::vector<std::pair<std::string, std::string>>& result);

  bool isVarModifiedAlongPath(int s1, int s2, const std::string& v);

  bool isVarModifiedAlongPathHelper(int currentStmtNum, int targetStmtNum,
                                    const std::string& v,
                                    std::unordered_set<int>& visited);

  bool isCallReadAssign(int statementNumber);
};
