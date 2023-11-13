#include "PKBReader.h"

void PKBReader::clearCache() {
  affectsCache.clearCache();
  nextStore.clearCache();
}
