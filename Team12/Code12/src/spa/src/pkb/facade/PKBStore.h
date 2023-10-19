#pragma once

#include "pkb/storage/CallsSStore.h"
#include "pkb/storage/CallsStore.h"
#include "pkb/storage/EntityStore.h"
#include "pkb/storage/FollowsStore.h"
#include "pkb/storage/ModifiesPStore.h"
#include "pkb/storage/ModifiesSStore.h"
#include "pkb/storage/NextStore.h"
#include "pkb/storage/ParentStore.h"
#include "pkb/storage/RelationTStore.h"
#include "pkb/storage/StmtStore.h"
#include "pkb/storage/UsesPStore.h"
#include "pkb/storage/UsesSStore.h"
#include "pkb/storage/pattern_storage/PatternStorage.h"

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
