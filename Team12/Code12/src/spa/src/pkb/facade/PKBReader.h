#pragma once

#include "pkb/facade/PKBStorage.h"
#include "pkb/readers/DesignEntitiesReader.h"
#include "pkb/readers/FollowsReader.h"
#include "pkb/readers/ModifiesReader.h"
#include "pkb/readers/ParentReader.h"
#include "pkb/readers/PatternReader.h"
#include "pkb/readers/UsesReader.h"

class PKBReader : public virtual DesignEntitiesReader,
                  public virtual FollowsReader,
                  public virtual ModifiesReader,
                  public virtual ParentReader,
                  public virtual PatternReader,
                  public virtual UsesReader {
 public:
  explicit PKBReader(PKBStorage& storage)
      : DesignEntitiesReader(storage, storage),
        FollowsReader(storage, storage),
        ModifiesReader(storage, storage, storage),
        ParentReader(storage, storage),
        PatternReader(storage),
        UsesReader(storage, storage, storage) {}
};
