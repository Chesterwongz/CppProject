#pragma once

#include "pkb/facade/PKBStorage.h"
#include "pkb/readers/entity_reader/DesignEntitiesReader.h"
#include "pkb/readers/pattern_reader/PatternReader.h"
#include "pkb/readers/relation_reader/CallsReader.h"
#include "pkb/readers/relation_reader/ModifiesReader.h"
#include "pkb/readers/relation_reader/NextReader.h"
#include "pkb/readers/relation_reader/UsesReader.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/FollowsReader.h"
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
