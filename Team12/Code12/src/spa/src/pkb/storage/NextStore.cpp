#include "NextStore.h"

void NextStore::precomputeRelationT(int from, int to) {}

void NextStore::computeSuccessorsT(int from) {
  this->computeRelationT(from, this->directSuccessorMap,
                         this->transitiveSuccessorMap);
}

void NextStore::computeAncestorsT(int to) {
  this->computeRelationT(to, this->directAncestorMap,
                         this->transitiveAncestorMap);
}

void NextStore::computeAllRelationsT() {
  for (const auto& [a, _] : this->directSuccessorMap) {
    if (this->directSuccessorMap.size() ==
        this->transitiveSuccessorMap.size()) {
      return;  // Optimization.
    }
    computeSuccessorsT(a);
  }
}

void NextStore::clearCache() {
  transitiveAncestorMap.clear();
  transitiveSuccessorMap.clear();
}
