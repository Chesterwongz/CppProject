#pragma once

#include "pkb/storage/relation_storage/stmt_or_proc_to_var/ModifiesStorage.h"
#include "pkb/storage/relation_storage/stmt_or_proc_to_var/UsesStorage.h"
#include "pkb/storage/relation_storage/stmt_to_stmt/FollowsStorage.h"
#include "pkb/storage/relation_storage/stmt_to_stmt/ParentStorage.h"

class RelationStorage : public virtual FollowsStorage,
                        public virtual ParentStorage,
                        public virtual UsesStorage,
                        public virtual ModifiesStorage {};
