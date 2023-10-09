#pragma once

#include "pkb/storage/cfg_storage/CfgStorage.h"
#include "pkb/storage/entity_storage/DesignEntitiesStorage.h"
#include "pkb/storage/entity_storage/StmtStorage.h"
#include "pkb/storage/pattern_storage/PatternStorage.h"
#include "pkb/storage/relation_storage/RelationStorage.h"

class PKBStorage : public CfgStorage,
                   public DesignEntitiesStorage,
                   public PatternStorage,
                   public RelationStorage,
                   public StmtStorage {};
