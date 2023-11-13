#include "AffectsCache.h"

void AffectsCache::clearCache() {
  directAncestorMap.clear();
  directSuccessorMap.clear();
  isComplete = false;
}

void AffectsCache::setIsComplete() { isComplete = true; }

bool AffectsCache::getIsComplete() const { return isComplete; }
