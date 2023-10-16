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
  std::unordered_map<S, std::unordered_set<T>> successorMap;

  // An unordered set of the direct ancestors of S. I.e., S <-* T
  std::unordered_map<T, std::unordered_set<S>> ancestorMap;

  void addRelationT(S from, T to) {
    successorMap[from].insert(to);
    ancestorMap[to].insert(from);
  }

 public:
  void addRelation(S from, T to) override {
    RelationStore<S, T>::addRelation(from, to);
    precomputeRelationT(from, to);
  }

  virtual void precomputeRelationT(S from, T to) {
    addRelationT(from, to);
    for (auto& s : this->directAncestorMap[from]) {
      addRelationT(s, to);
    }
    for (auto& s : this->directSuccessorMap[to]) {
      addRelationT(from, s);
    }
  }

  [[nodiscard]] bool hasRelationT(S from, T to) const {
    return successorMap.count(from) && successorMap.at(from).count(to);
  }

  [[nodiscard]] std::vector<T> getAllSuccessorsTOf(S from) const {
    return RelationStore<S, T>::relationToVector(from, successorMap);
  }

  [[nodiscard]] std::vector<T> getSuccessorsTOf(
      S from, const std::function<bool(T)>& filter) const {
    return RelationStore<S, T>::relationToVectorFiltered(from, successorMap,
                                                         filter);
  }

  [[nodiscard]] std::vector<S> getAllAncestorsTOf(T to) const {
    return RelationStore<S, T>::relationToVector(to, ancestorMap);
  }

  [[nodiscard]] std::vector<S> getAncestorsTOf(
      T to, const std::function<bool(S)>& filter) const {
    return RelationStore<S, T>::relationToVectorFiltered(to, ancestorMap,
                                                         filter);
  }

  [[nodiscard]] std::vector<std::pair<S, T>> getRelationsT(
      std::pair<const std::function<bool(S)>&, const std::function<bool(T)>&>
          filterStmtPair) const {
    return RelationStore<S, T>::allRelationsToVectorFiltered(
        successorMap, filterStmtPair.first, filterStmtPair.second);
  }

  [[nodiscard]] std::vector<std::pair<S, T>> getAllRelationsT() const {
    return RelationStore<S, T>::allRelationsToVector(successorMap);
  }
};
