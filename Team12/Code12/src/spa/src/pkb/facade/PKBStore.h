#pragma once

#include "pkb/storage/entity_storage/EntityStore.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/pattern_storage/PatternStorage.h"
#include "pkb/storage/relation_storage/CallsSStore.h"
#include "pkb/storage/relation_storage/CallsStore.h"
#include "pkb/storage/relation_storage/FollowsStore.h"
#include "pkb/storage/relation_storage/ModifiesPStore.h"
#include "pkb/storage/relation_storage/ModifiesSStore.h"
#include "pkb/storage/relation_storage/NextStore.h"
#include "pkb/storage/relation_storage/ParentStore.h"
#include "pkb/storage/relation_storage/RelationTStore.h"
#include "pkb/storage/relation_storage/UsesPStore.h"
#include "pkb/storage/relation_storage/UsesSStore.h"

class PKBStore {
 private:
  FollowsStore followsStore;
  ParentStore parentStore;
  NextStore nextStore;

  ModifiesSStore modifiesStore;
  ModifiesPStore modifiesProcStore;
  UsesSStore usesStore;
  UsesPStore usesProcStore;

  CallsStore callsStore;
  CallsSStore callsStmtStore;

  StmtStore stmtStore;
  EntityStore entityStore;

  PatternStorage patternStore;

 public:
  [[nodiscard]] FollowsStore& getFollowsStore();
  [[nodiscard]] ParentStore& getParentStore();
  [[nodiscard]] NextStore& getNextStore();
  [[nodiscard]] ModifiesSStore& getModifiesStore();
  [[nodiscard]] ModifiesPStore& getModifiesProcStore();
  [[nodiscard]] UsesSStore& getUsesStore();
  [[nodiscard]] UsesPStore& getUsesProcStore();
  [[nodiscard]] CallsStore& getCallsStore();
  [[nodiscard]] CallsSStore& getCallsStmtStore();
  [[nodiscard]] StmtStore& getStmtStore();
  [[nodiscard]] EntityStore& getEntityStore();
  [[nodiscard]] PatternStorage& getPatternStore();
};
