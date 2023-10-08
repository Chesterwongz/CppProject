#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"
#include "pkb/storage/entitystorage/DesignEntitiesStorage.h"
#include "pkb/storage/relationshipstorage/FollowsStorage.h"
#include "pkb/storage/relationshipstorage/ModifiesStorage.h"
#include "pkb/storage/relationshipstorage/ParentStorage.h"
#include "pkb/storage/patternstorage/PatternStorage.h"
#include "pkb/storage/entitystorage/StmtStorage.h"
#include "pkb/storage/relationshipstorage/UsesStorage.h"
#include "pkb/storage/relationshipstorage/RelationshipStorage.h"

class PKBStorage : public virtual DesignEntitiesStorage,
                   public virtual PatternStorage,
                   public virtual RelationshipStorage,
                   public virtual StmtStorage {};
