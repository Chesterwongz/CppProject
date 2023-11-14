#include "ClauseCache.h"

#include <cassert>

bool ClauseCache::isCacheHit(const ClauseKey& clauseKey) const {
  return this->cache.find(clauseKey) != this->cache.end();
}

IntermediateTable ClauseCache::getResFromCache(
    const ClauseKey& clauseKey) const {
  assert(this->isCacheHit(clauseKey));
  return this->cache.at(clauseKey);
}

void ClauseCache::saveToCache(const ClauseKey& clauseKey,
                              const IntermediateTable& table) {
  // save copy of table in cache
  this->cache.insert(std::make_pair(clauseKey, table));
}

void ClauseCache::clearCache() { this->cache.clear(); }
