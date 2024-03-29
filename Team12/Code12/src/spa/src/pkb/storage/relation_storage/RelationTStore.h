#pragma once

#include <algorithm>
#include <functional>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "RelationStore.h"

template <typename T>
class RelationTStore : public RelationStore<T, T> {
 protected:
  // An unordered set of the direct successors of T. I.e., T *-> T
  std::unordered_map<T, std::unordered_set<T>> transitiveSuccessorMap;

  // An unordered set of the direct ancestors of T. I.e., T <-* T
  std::unordered_map<T, std::unordered_set<T>> transitiveAncestorMap;
  bool isPrecomputed = false;

  // DFS to compute transitive closure of vertex
  void computeRelationT(
      T key, std::unordered_map<T, std::unordered_set<T>>& directMap,
      std::unordered_map<T, std::unordered_set<T>>& transitiveMap) {
    if (transitiveMap.count(key) || !directMap.count(key)) {
      return;  // nothing to compute.
    }

    std::unordered_set<T> visitedSet;
    std::stack<T> toVisit;
    for (const auto& directNbrs : directMap.at(key)) {
      toVisit.push(directNbrs);
    }
    while (!toVisit.empty()) {
      T curr = toVisit.top();
      toVisit.pop();
      visitedSet.insert(curr);

      if (!directMap.count(curr)) continue;
      if (transitiveMap.count(curr)) {
        const auto& currTransNbrs = transitiveMap.at(curr);
        visitedSet.reserve(currTransNbrs.size());
        visitedSet.insert(currTransNbrs.begin(), currTransNbrs.end());
        continue;
      }
      for (const auto& nbr : directMap.at(curr)) {
        if (!visitedSet.count(nbr)) {
          toVisit.push(nbr);
        }
      }
    }
    if (!visitedSet.empty()) {
      transitiveMap[key] = std::move(visitedSet);
    }
  }

 public:
  void addRelation(T from, T to) override {
    RelationStore<T, T>::addRelation(from, to);
  }

  [[nodiscard]] bool hasSuccessorsT(T from) {
    computeSuccessorsT(from);
    return transitiveSuccessorMap.count(from);
  }

  [[nodiscard]] const std::unordered_set<T>& getSuccessorsT(T from) const {
    return transitiveSuccessorMap.at(from);
  }

  [[nodiscard]] std::unordered_set<T> getSuccessorsT() {
    computeAllRelationsT();
    std::unordered_set<T> result;
    result.reserve(transitiveAncestorMap.size());
    std::transform(transitiveAncestorMap.begin(), transitiveAncestorMap.end(),
                   std::inserter(result, result.end()),
                   [](const auto& pair) { return pair.first; });
    return result;
  }

  [[nodiscard]] bool hasAncestorsT(T to) {
    computeAncestorsT(to);
    return transitiveAncestorMap.count(to);
  }

  [[nodiscard]] const std::unordered_set<T>& getAncestorsT(T to) const {
    return transitiveAncestorMap.at(to);
  }

  [[nodiscard]] std::unordered_set<T> getAncestorsT() {
    computeAllRelationsT();
    std::unordered_set<T> result;
    result.reserve(transitiveSuccessorMap.size());
    std::transform(transitiveSuccessorMap.begin(), transitiveSuccessorMap.end(),
                   std::inserter(result, result.end()),
                   [](const auto& pair) { return pair.first; });
    return result;
  }

  [[nodiscard]] bool hasRelationT(T from, T to) {
    return hasSuccessorsT(from) && transitiveSuccessorMap.at(from).count(to);
  }

  [[nodiscard]] const std::unordered_map<T, std::unordered_set<T>>&
  getRelationsT() {
    computeAllRelationsT();
    return transitiveSuccessorMap;
  }

  void computeSuccessorsT(T from) {
    this->computeRelationT(from, this->directSuccessorMap,
                           this->transitiveSuccessorMap);
  }

  void computeAncestorsT(T to) {
    this->computeRelationT(to, this->directAncestorMap,
                           this->transitiveAncestorMap);
  }

  void computeAllRelationsT() {
    if (isPrecomputed) return;
    std::vector<T> graphVector;
    graphVector.reserve(this->directSuccessorMap.size());
    for (const auto& [v, _] : this->directSuccessorMap) {
      graphVector.push_back(v);
    }
    // Optimization
    std::sort(graphVector.begin(), graphVector.end(),
              std::greater<>());  // Sort in descending order
    for (const auto& v : graphVector) {
      computeSuccessorsT(v);
    }
    for (const auto& [a, successors] : transitiveSuccessorMap) {
      for (const auto& s : successors) {
        transitiveAncestorMap[s].insert(a);
      }
    }
    isPrecomputed = true;
  }
};
