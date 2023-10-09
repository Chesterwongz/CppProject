#pragma once

#include "pkb/storage/entity_storage/DesignEntitiesStorage.h"
#include "pkb/storage/entity_storage/StmtStorage.h"
#include "pkb/storage/pattern_storage/PatternStorage.h"
#include "pkb/storage/relation_storage/RelationStorage.h"

class PKBStorage : public virtual DesignEntitiesStorage,
                   public virtual PatternStorage,
                   public virtual RelationStorage,
                   public virtual StmtStorage {};
