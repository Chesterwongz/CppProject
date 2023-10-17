#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "RelationStore.h"

template <typename S, typename T>
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

 public:
  void addRelation(S from, T to) override {
    RelationStore<S, T>::addRelation(from, to);
    precomputeRelationT(from, to);
  }

  [[nodiscard]] bool hasRelationT(S from, T to) const {
    return transitiveSuccessorMap.count(from) &&
           transitiveSuccessorMap.at(from).count(to);
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

  [[nodiscard]] std::vector<std::pair<S, T>> getRelationsT(
      std::pair<const std::function<bool(S)>&, const std::function<bool(T)>&>
          filterStmtPair) const {
    return RelationStore<S, T>::allRelationsToVectorFiltered(
        transitiveSuccessorMap, filterStmtPair.first, filterStmtPair.second);
  }

  [[nodiscard]] std::vector<std::pair<S, T>> getAllRelationsT() const {
    return RelationStore<S, T>::allRelationsToVector(transitiveSuccessorMap);
  }
};
