#pragma once

#include "pkb/facade/PKBStorage.h"
#include "pkb/readers/entity_reader/DesignEntitiesReader.h"
#include "pkb/readers/pattern_reader/PatternReader.h"
#include "pkb/readers/relation_reader/proc_to_proc/CallsReader.h"
#include "pkb/readers/relation_reader/stmt_proc_to_var/ModifiesReader.h"
#include "pkb/readers/relation_reader/stmt_proc_to_var/UsesReader.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/FollowsReader.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/NextReader.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/ParentReader.h"

class PKBReader : public DesignEntitiesReader,
                  public FollowsReader,
                  public ModifiesReader,
                  public NextReader,
                  public ParentReader,
                  public PatternReader,
                  public UsesReader,
                  public CallsReader {
 public:
  explicit PKBReader(PKBStorage& storage)
      : DesignEntitiesReader(storage, storage),
        FollowsReader(storage, storage),
        ModifiesReader(storage, storage, storage),
        NextReader(storage, storage, storage),
        ParentReader(storage, storage),
        PatternReader(storage),
        UsesReader(storage, storage, storage),
        CallsReader(storage) {}
};
