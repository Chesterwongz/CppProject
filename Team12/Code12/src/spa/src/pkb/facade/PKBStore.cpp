#include "PKBStore.h"

FollowsStore& PKBStore::getFollowsStore() { return followsStore; }

ParentStore& PKBStore::getParentStore() { return parentStore; }

NextStore& PKBStore::getNextStore() { return nextStore; }

ModifiesSStore& PKBStore::getModifiesStore() { return modifiesStore; }

ModifiesPStore& PKBStore::getModifiesProcStore() { return modifiesProcStore; }

UsesSStore& PKBStore::getUsesStore() { return usesStore; }

UsesPStore& PKBStore::getUsesProcStore() { return usesProcStore; }

CallsStore& PKBStore::getCallsStore() { return callsStore; }

CallsSStore& PKBStore::getCallsStmtStore() { return callsStmtStore; }

StmtStore& PKBStore::getStmtStore() { return stmtStore; }

EntityStore& PKBStore::getEntityStore() { return entityStore; }

PatternStorage& PKBStore::getPatternStore() { return patternStore; }
