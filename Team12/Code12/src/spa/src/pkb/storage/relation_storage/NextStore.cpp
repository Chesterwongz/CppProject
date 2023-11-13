#include "NextStore.h"

void NextStore::clearCache() {
  transitiveAncestorMap.clear();
  transitiveSuccessorMap.clear();
  isPrecomputed = false;
}
