#pragma once

#include "pkb/storage/relation_storage/proc_to_proc/CallsStorage.h"
#include "pkb/storage/relation_storage/stmt_or_proc_to_var/ModifiesStorage.h"
#include "pkb/storage/relation_storage/stmt_or_proc_to_var/UsesStorage.h"
#include "pkb/storage/relation_storage/stmt_to_stmt/FollowsStorage.h"
#include "pkb/storage/relation_storage/stmt_to_stmt/NextStorage.h"
#include "pkb/storage/relation_storage/stmt_to_stmt/ParentStorage.h"

class RelationStorage : public FollowsStorage,
                        public ParentStorage,
                        public UsesStorage,
                        public ModifiesStorage,
                        public CallsStorage,
                        public NextStorage {};
