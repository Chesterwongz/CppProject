#pragma once

#include "pkb/storage/CallsStore.h"
#include "pkb/storage/FollowsStore.h"
#include "pkb/storage/ModifiesPStore.h"
#include "pkb/storage/ModifiesStore.h"
#include "pkb/storage/NextStore.h"
#include "pkb/storage/ParentStore.h"
#include "pkb/storage/RelationTStore.h"
#include "pkb/storage/StmtStore.h"
#include "pkb/storage/UsesPStore.h"
#include "pkb/storage/UsesStore.h"

class PKBStore {
 private:
  FollowsStore followsStore;
  ParentStore parentStore;
  NextStore nextStore;

  ModifiesStore modifiesStore;
  ModifiesPStore modifiesProcStore;
  UsesStore usesStore;
  UsesPStore usesProcStore;

  CallsStore callsStore;

  StmtStore stmtStore;

 public:
  [[nodiscard]] FollowsStore& getFollowsStore();
  [[nodiscard]] ParentStore& getParentStore();
  [[nodiscard]] NextStore& getNextStore();
  [[nodiscard]] ModifiesStore& getModifiesStore();
  [[nodiscard]] ModifiesPStore& getModifiesProcStore();
  [[nodiscard]] UsesStore& getUsesStore();
  [[nodiscard]] UsesPStore& getUsesProcStore();
  [[nodiscard]] CallsStore& getCallsStore();
  [[nodiscard]] StmtStore& getStmtStore();
};
