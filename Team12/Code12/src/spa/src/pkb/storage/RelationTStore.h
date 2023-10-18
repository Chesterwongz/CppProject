#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "RelationStore.h"

template <typename S, typename T = S>
class RelationTStore : public RelationStore<S, T> {
 protected:
  // An unordered set of the direct successors of S. I.e., S *-> T
  std::unordered_map<S, std::unordered_set<T>> transitiveSuccessorMap;

  // An unordered set of the direct ancestors of S. I.e., S <-* T
  std::unordered_map<T, std::unordered_set<S>> transitiveAncestorMap;

  RelationTStore() = default;

  void addRelationT(S from, T to) {
    transitiveSuccessorMap[from].insert(to);
    transitiveAncestorMap[to].insert(from);
  }

  virtual void precomputeRelationT(S from, T to) {
    addRelationT(from, to);
    for (const auto& s : transitiveAncestorMap[from]) {
      addRelationT(s, to);
    }
    for (const auto& t : transitiveSuccessorMap[to]) {
      addRelationT(from, t);
    }
  }

  template <typename K, typename V = K>
  void computeRelationT(
      K key, std::unordered_map<K, std::unordered_set<V>>& directMap,
      std::unordered_map<K, std::unordered_set<V>>& transitiveMap,
      std::unordered_set<V>& visitedSet) {
    if (transitiveMap.count(key) || !directMap.count(key)) {
      return;  // nothing to compute.
    }
    std::unordered_set<K> transitiveSet;
    for (const auto& s : directMap.at(key)) {
      if (visitedSet.count(s)) continue;
      visitedSet.insert(s);
      computeRelationT(s, directMap, transitiveMap, visitedSet);
      if (this->transitiveSuccessorMap.count(s)) {
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
  virtual void computeSuccessorsT(S from) {}
  virtual void computeAllRelationsT() {}

 public:
  void addRelation(S from, T to) override {
    RelationStore<S, T>::addRelation(from, to);
    precomputeRelationT(from, to);
  }

  [[nodiscard]] bool hasRelationT(S from, T to) {
    return hasSuccessorsT(from) && transitiveSuccessorMap.at(from).count(to);
  }

  [[nodiscard]] bool hasSuccessorsT(S from) {
    computeSuccessorsT(from);
    return transitiveSuccessorMap.count(from);
  }

  [[nodiscard]] bool hasAncestorsT(T to) {
    computeAncestorsT(to);
    return transitiveAncestorMap.count(to);
  }

  [[nodiscard]] const std::unordered_set<T>& getSuccessorsT(S from) const {
    return transitiveSuccessorMap.at(from);
  }

  [[nodiscard]] const std::unordered_set<T>& getAncestorsT(T to) const {
    return transitiveAncestorMap.at(to);
  }

  [[nodiscard]] std::vector<T> getAllSuccessorsTOf(S from) const {
    return RelationStore<S, T>::relationToVector(from, transitiveSuccessorMap);
  }

  [[nodiscard]] std::vector<T> getSuccessorsTOf(
      S from, const std::function<bool(T)>& filter) const {
    return RelationStore<S, T>::relationToVectorFiltered(
        from, transitiveSuccessorMap, filter);
  }

  [[nodiscard]] std::vector<S> getAllAncestorsTOf(T to) const {
    return RelationStore<S, T>::relationToVector(to, transitiveAncestorMap);
  }

  [[nodiscard]] std::vector<S> getAncestorsTOf(
      T to, const std::function<bool(S)>& filter) const {
    return RelationStore<S, T>::relationToVectorFiltered(
        to, transitiveAncestorMap, filter);
  }

  [[nodiscard]] std::vector<std::pair<S, T>> getAllRelationsT() const {
    return RelationStore<S, T>::allRelationsToVector(transitiveSuccessorMap);
  }

  [[nodiscard]] std::vector<std::pair<S, T>> getRelationsT(
      std::pair<const std::function<bool(S)>&, const std::function<bool(T)>&>
          filterStmtPair) const {
    return RelationStore<S, T>::allRelationsToVectorFiltered(
        transitiveSuccessorMap, filterStmtPair.first, filterStmtPair.second);
  }

  [[nodiscard]] const std::unordered_map<S, std::unordered_set<T>>&
  getRelationsT() {
    computeAllRelationsT();
    return transitiveSuccessorMap;
  }
};
