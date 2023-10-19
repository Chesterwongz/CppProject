#pragma once

#include <functional>
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

  void computeRelationT(
      T key, std::unordered_map<T, std::unordered_set<T>>& directMap,
      std::unordered_map<T, std::unordered_set<T>>& transitiveMap,
      std::unordered_map<T, int>& visited) {
    constexpr int kVisited = 2;
    if (transitiveMap.count(key) || !directMap.count(key)) {
      return;  // nothing to compute.
    }
    std::unordered_set<T> transitiveSet;
    for (const auto& s : directMap.at(key)) {
      if (visited[s] == kVisited) continue;
      visited[s]++;
      computeRelationT(s, directMap, transitiveMap, visited);
      if (transitiveMap.count(s)) {
        const auto& sT = transitiveMap.at(s);
        transitiveSet.reserve(sT.size() + 1);
        transitiveSet.insert(sT.begin(), sT.end());
      }
      transitiveSet.insert(s);
    }
    if (!transitiveSet.empty()) {
      transitiveMap[key] = transitiveSet;
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

  [[nodiscard]] const std::unordered_set<T>& getAncestorsS(T to) const {
    return transitiveAncestorMap.at(to);
  }

  [[nodiscard]] std::vector<T> getSuccessorsTOf(
      T from, const std::function<bool(T)>& filter) const {
    return RelationStore<T, T>::relationToVectorFiltered(
        from, transitiveSuccessorMap, filter);
  }

  [[nodiscard]] std::vector<T> getAllAncestorsTOf(T to) const {
    return RelationStore<T, T>::relationToVector(to, transitiveAncestorMap);
  }

  [[nodiscard]] std::vector<T> getAncestorsTOf(
      T to, const std::function<bool(T)>& filter) const {
    return RelationStore<T, T>::relationToVectorFiltered(
        to, transitiveAncestorMap, filter);
  }

  [[nodiscard]] std::vector<std::pair<T, T>> getRelationsT(
      std::pair<const std::function<bool(T)>&, const std::function<bool(T)>&>
          filterStmtPair) const {
    return RelationStore<T, T>::allRelationsToVectorFiltered(
        transitiveSuccessorMap, filterStmtPair.first, filterStmtPair.second);
  }

  [[nodiscard]] const std::unordered_map<T, std::unordered_set<T>>&
  getRelationsT() {
    computeAllRelationsT();
    return transitiveSuccessorMap;
  }
};
