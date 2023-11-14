#pragma once

#include <string>

#include "pkb/storage/AffectsCache.h"
#include "pkb/storage/entity_storage/EntityStore.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/pattern_storage/PatternStorage.h"
#include "pkb/storage/relation_storage/NextStore.h"
#include "pkb/storage/relation_storage/RelationStore.h"
#include "pkb/storage/relation_storage/RelationTStore.h"

class PKBStore {
 private:
  AffectsCache affectsCache;
  RelationTStore<int> followsStore;
  RelationTStore<int> parentStore;
  NextStore nextStore;

  RelationStore<int, std::string> modifiesStore;
  RelationStore<std::string, std::string> modifiesProcStore;
  RelationStore<int, std::string> usesStore;
  RelationStore<std::string, std::string> usesProcStore;

  RelationTStore<std::string> callsStore;
  RelationStore<int, std::string> callsStmtStore;

  StmtStore stmtStore;
  EntityStore entityStore;

  PatternStorage patternStore;

 public:
  [[nodiscard]] AffectsCache& getAffectsCache();
  [[nodiscard]] RelationTStore<int>& getFollowsStore();
  [[nodiscard]] RelationTStore<int>& getParentStore();
  [[nodiscard]] NextStore& getNextStore();
  [[nodiscard]] RelationStore<int, std::string>& getModifiesStore();
  [[nodiscard]] RelationStore<std::string, std::string>& getModifiesProcStore();
  [[nodiscard]] RelationStore<int, std::string>& getUsesStore();
  [[nodiscard]] RelationStore<std::string, std::string>& getUsesProcStore();
  [[nodiscard]] RelationTStore<std::string>& getCallsStore();
  [[nodiscard]] RelationStore<int, std::string>& getCallsStmtStore();
  [[nodiscard]] StmtStore& getStmtStore();
  [[nodiscard]] EntityStore& getEntityStore();
  [[nodiscard]] PatternStorage& getPatternStore();
};
