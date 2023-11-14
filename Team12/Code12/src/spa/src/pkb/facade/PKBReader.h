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
#include "pkb/storage/AffectsCache.h"
#include "pkb/storage/relation_storage/NextStore.h"

class PKBReader : public AffectsReader,
                  public DesignEntitiesReader,
                  public FollowsReader,
                  public ModifiesReader,
                  public NextReader,
                  public ParentReader,
                  public PatternReader,
                  public UsesReader,
                  public CallsReader {
  AffectsCache& affectsCache;
  NextStore& nextStore;

 public:
  explicit PKBReader(PKBStore& store)
      : affectsCache(store.getAffectsCache()),
        nextStore(store.getNextStore()),
        AffectsReader(store.getAffectsCache(), store.getModifiesStore(),
                      store.getNextStore(), store.getStmtStore(),
                      store.getUsesStore()),
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
