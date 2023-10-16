#include "PKBStore.h"

FollowsStore& PKBStore::getFollowsStore() { return followsStore; }

ParentStore& PKBStore::getParentStore() { return parentStore; }

NextStore& PKBStore::getNextStore() { return nextStore; }

ModifiesStore& PKBStore::getModifiesStore() { return modifiesStore; }

ModifiesPStore& PKBStore::getModifiesProcStore() { return modifiesProcStore; }

UsesStore& PKBStore::getUsesStore() { return usesStore; }

UsesPStore& PKBStore::getUsesProcStore() { return usesProcStore; }

CallsStore& PKBStore::getCallsStore() { return callsStore; }

CallsSStore& PKBStore::getCallsStmtStore() { return callsStmtStore; }

StmtStore& PKBStore::getStmtStore() { return stmtStore; }
