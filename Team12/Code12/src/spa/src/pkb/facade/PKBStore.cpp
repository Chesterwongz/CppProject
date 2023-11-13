#include "PKBStore.h"

AffectsCache& PKBStore::getAffectsCache() { return affectsCache; }

RelationTStore<int>& PKBStore::getFollowsStore() { return followsStore; }

RelationTStore<int>& PKBStore::getParentStore() { return parentStore; }

NextStore& PKBStore::getNextStore() { return nextStore; }

RelationStore<int, std::string>& PKBStore::getModifiesStore() {
  return modifiesStore;
}

RelationStore<std::string, std::string>& PKBStore::getModifiesProcStore() {
  return modifiesProcStore;
}

RelationStore<int, std::string>& PKBStore::getUsesStore() { return usesStore; }

RelationStore<std::string, std::string>& PKBStore::getUsesProcStore() {
  return usesProcStore;
}

RelationTStore<std::string>& PKBStore::getCallsStore() { return callsStore; }

RelationStore<int, std::string>& PKBStore::getCallsStmtStore() {
  return callsStmtStore;
}

StmtStore& PKBStore::getStmtStore() { return stmtStore; }

EntityStore& PKBStore::getEntityStore() { return entityStore; }

PatternStorage& PKBStore::getPatternStore() { return patternStore; }
