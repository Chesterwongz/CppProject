#pragma once

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <utility>

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

  bool hasRelationT(S from, T to) const {
    return successorMap.count(from) && successorMap.at(from).count(to);
  }

  //  std::unordered_set<T>& getAllSuccessors(S from) const {
  //    return successorMap[from];
  //  }
  //  std::unordered_set<S>& getAllAncestors(T to) const { return
  //  ancestorMap[to]; }

  std::vector<S> getAncestorsOf(T to,
                                const std::function<bool(S)>& filter) const {
    std::vector<S> res;
    const auto& setS = ancestorMap.at(to);
    std::copy_if(setS.begin(), setS.end(), std::back_inserter(res), filter);
    return res;
  }

  std::vector<T> getSuccessorsOf(S from,
                                 const std::function<bool(S)>& filter) const {
    std::vector<T> res;
    const auto& setT = successorMap.at(from);
    std::copy_if(setT.begin(), setT.end(), std::back_inserter(res), filter);
    return res;
  }

  std::vector<std::pair<S, T>> getAllRelationsT(
      const std::function<bool(S)>& filterStmt1,
      const std::function<bool(T)>& filterStmt2) const {
    return RelationStore<S, T>::flatMap(successorMap, filterStmt1, filterStmt2);
  }
};
