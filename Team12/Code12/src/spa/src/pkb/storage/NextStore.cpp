#include "NextStore.h"

void NextStore::precomputeRelationT(int from, int to) {}

void NextStore::computeSuccessorsT(int from) {
  std::unordered_map<int, int> visited = {};
  this->computeRelationT(from, this->directSuccessorMap,
                         this->transitiveSuccessorMap, visited);
}

void NextStore::computeAncestorsT(int to) {
  std::unordered_map<int, int> visited = {};
  this->computeRelationT(to, this->directAncestorMap,
                         this->transitiveAncestorMap, visited);
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
