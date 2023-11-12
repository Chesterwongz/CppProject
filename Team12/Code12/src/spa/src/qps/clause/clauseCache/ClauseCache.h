#pragma once

#include <unordered_map>
#include <utility>git

#include "qps/intermediateTable/IntermediateTable.h"

typedef string ClauseKey;

class ClauseCache {
  unordered_map<ClauseKey, IntermediateTable> cache {};

 public:
  [[nodiscard]] bool isCacheHit(const ClauseKey& clauseKey) const;
  [[nodiscard]] IntermediateTable getResFromCache(
      const ClauseKey& clauseKey) const;
  void saveToCache(const ClauseKey& clauseKey, const IntermediateTable& table);
  void clearCache();
};
