#pragma once

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

  RelationTStore() = default;

  void addRelationT(T from, T to) {
    transitiveSuccessorMap[from].insert(to);
    transitiveAncestorMap[to].insert(from);
  }

  virtual void precomputeRelationT(T from, T to) {
    addRelationT(from, to);
    for (const auto& s : transitiveAncestorMap[from]) {
      addRelationT(s, to);
    }
    for (const auto& t : transitiveSuccessorMap[to]) {
      addRelationT(from, t);
    }
  }

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

  virtual void computeAncestorsT(T to) {}
  virtual void computeSuccessorsT(T from) {}
  virtual void computeAllRelationsT() {}

 public:
  void addRelation(T from, T to) override {
    RelationStore<T, T>::addRelation(from, to);
    precomputeRelationT(from, to);
  }

  [[nodiscard]] bool hasRelationT(T from, T to) {
    return hasSuccessorsT(from) && transitiveSuccessorMap.at(from).count(to);
  }

  [[nodiscard]] bool hasSuccessorsT(T from) {
    computeSuccessorsT(from);
    return transitiveSuccessorMap.count(from);
  }

  [[nodiscard]] bool hasAncestorsT(T to) {
    computeAncestorsT(to);
    return transitiveAncestorMap.count(to);
  }

  [[nodiscard]] const std::unordered_set<T>& getSuccessorsT(T from) const {
    return transitiveSuccessorMap.at(from);
  }

  [[nodiscard]] const std::unordered_set<T>& getAncestorsT(T to) const {
    return transitiveAncestorMap.at(to);
  }

  [[nodiscard]] const std::unordered_map<T, std::unordered_set<T>>&
  getRelationsT() {
    computeAllRelationsT();
    return transitiveSuccessorMap;
  }
};
