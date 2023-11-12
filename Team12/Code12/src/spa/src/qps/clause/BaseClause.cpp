#include "BaseClause.h"

bool BaseClause::isDisableCaching() { return false; }

IntermediateTable BaseClause::evaluate(PKBReader& pkb, ClauseCache& cache) {
  if (this->isDisableCaching()) {
    return this->evaluate(pkb);
  }

  ClauseKey key = this->getKey();
  // check cache first
  if (cache.isCacheHit(key)) {
    return std::move(cache.getResFromCache(key));
  } else {
    IntermediateTable res = this->evaluate(pkb);
    cache.saveToCache(key, res);
    return res;
  }
}
