#pragma once

#include "ParentStorage.h"
#include "pkb/storage/patternstorage/PatternStorage.h"
#include "FollowsStorage.h"
#include "UsesModifiesStorage.h"

class RelationshipStorage : public virtual FollowsStorage,
                            public virtual ParentStorage,
                            public virtual UsesModifiesStorage {};
