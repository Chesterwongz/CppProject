#pragma once

#include "PKBStore.h"
#include "pkb/readers/entity_reader/DesignEntitiesReader.h"
#include "pkb/readers/pattern_reader/PatternReader.h"
#include "pkb/readers/relation_reader/proc_to_proc/CallsReader.h"
#include "pkb/readers/relation_reader/stmt_proc_to_var/ModifiesReader.h"
#include "pkb/readers/relation_reader/stmt_proc_to_var/UsesReader.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/AffectsReader.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/FollowsReader.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/NextReader.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/ParentReader.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/relation_storage/CallsStore.h"
#include "pkb/storage/relation_storage/ModifiesPStore.h"
#include "pkb/storage/relation_storage/ModifiesSStore.h"
#include "pkb/storage/relation_storage/NextStore.h"
#include "pkb/storage/relation_storage/ParentStore.h"
#include "pkb/storage/relation_storage/RelationTStore.h"
#include "pkb/storage/relation_storage/UsesPStore.h"
#include "pkb/storage/relation_storage/UsesSStore.h"

class PKBReader : public AffectsReader,
                  public DesignEntitiesReader,
                  public FollowsReader,
                  public ModifiesReader,
                  public NextReader,
                  public ParentReader,
                  public PatternReader,
                  public UsesReader,
                  public CallsReader {
  NextStore& nextStore;

 public:
  explicit PKBReader(PKBStore& store)
      : nextStore(store.getNextStore()),
        AffectsReader(store.getModifiesStore(), store.getNextStore(),
                      store.getStmtStore(), store.getUsesStore()),
        DesignEntitiesReader(store.getCallsStmtStore(), store.getEntityStore(),
                             store.getModifiesStore(), store.getStmtStore(),
                             store.getUsesStore()),
        FollowsReader(store.getFollowsStore(), store.getStmtStore()),
        ModifiesReader(store.getModifiesStore(), store.getModifiesProcStore(),
                       store.getStmtStore()),
        NextReader(store.getNextStore(), store.getStmtStore()),
        ParentReader(store.getParentStore(), store.getStmtStore()),
        PatternReader(store.getPatternStore()),
        UsesReader(store.getUsesStore(), store.getUsesProcStore(),
                   store.getStmtStore()),
        CallsReader(store.getCallsStore()) {}

  void clearCache();
};
