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
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/relation_storage/NextStore.h"
#include "pkb/storage/relation_storage/RelationStore.h"

class AffectsReader : public IAffectsReader {
 private:
  AffectsCache& affectsCache;
  RelationStore<int, std::string>& modifiesSStore;
  NextStore& nextStore;
  StmtStore& stmtStore;
  RelationStore<int, std::string>& usesSStore;

  void processAffectsPairs(
      std::vector<std::pair<std::string, std::string>>& result,
      bool findOnlyFirst);
  std::vector<std::string> getAllAffectsS1();
  std::vector<std::string> getAllAffectsS2();
  std::vector<std::string> getUniqueAffects(
      const std::function<
          std::string(const std::pair<std::string, std::string>&)>& extractor);

 public:
  explicit AffectsReader(AffectsCache& affectsCache,
                         RelationStore<int, std::string>& modifiesSStore,
                         NextStore& nextStore, StmtStore& stmtStore,
                         RelationStore<int, std::string>& usesSStore)
      : affectsCache(affectsCache),
        modifiesSStore(modifiesSStore),
        nextStore(nextStore),
        stmtStore(stmtStore),
        usesSStore(usesSStore) {}

  std::vector<std::pair<std::string, std::string>> getAffectsPairs() override;

  bool isAffects(int firstStmtNum, int secondStmtNum) override;

  std::vector<std::string> getAffects(int s1, StmtType type2) override;
  std::vector<std::string> getAffectedBy(int s2, StmtType type1) override;

  void findAffectsPairs(
      int originalStmt, int currentStmt, const std::string& variable,
      std::unordered_set<std::string>& done,
      std::vector<std::pair<std::string, std::string>>& result);

  bool isCallReadAssign(int statementNumber);

  bool hasAffects() override;
};
