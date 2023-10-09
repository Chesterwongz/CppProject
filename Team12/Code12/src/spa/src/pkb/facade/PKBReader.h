#pragma once

#include "pkb/facade/PKBStorage.h"
#include "pkb/readers/CallsReader.h"
#include "pkb/readers/DesignEntitiesReader.h"
#include "pkb/readers/FollowsReader.h"
#include "pkb/readers/ModifiesReader.h"
#include "pkb/readers/ParentReader.h"
#include "pkb/readers/PatternReader.h"
#include "pkb/readers/UsesReader.h"

class PKBReader : public DesignEntitiesReader,
                  public FollowsReader,
                  public ModifiesReader,
                  public ParentReader,
                  public PatternReader,
                  public UsesReader,
                  public CallsReader {
 public:
  explicit PKBReader(PKBStorage& storage)
      : DesignEntitiesReader(storage, storage),
        FollowsReader(storage, storage),
        ModifiesReader(storage, storage, storage),
        ParentReader(storage, storage),
        PatternReader(storage),
        UsesReader(storage, storage, storage),
        CallsReader(storage) {}
};
