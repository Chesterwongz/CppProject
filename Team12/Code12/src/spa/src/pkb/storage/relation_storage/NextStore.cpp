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
  if (isFullyCached) return;
  std::vector<int> graphVector;
  graphVector.reserve(directSuccessorMap.size());
  for (const auto& [v, _] : this->directSuccessorMap) {
    graphVector.push_back(v);
  }
  // Optimization
  std::sort(graphVector.begin(), graphVector.end(),
            std::greater<>());  // Sort in descending order
  for (const auto& v : graphVector) {
    computeSuccessorsT(v);
  }
  isFullyCached = true;
}

void NextStore::clearCache() {
  transitiveAncestorMap.clear();
  transitiveSuccessorMap.clear();
  isFullyCached = false;
}
