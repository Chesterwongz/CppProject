#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename A, typename B>
class RelationStore {
 protected:
  // An unordered set of the direct successors of S. I.e., S -> T
  std::unordered_map<A, std::unordered_set<B>> directSuccessorMap;

  // An unordered set of the direct ancestors of S. I.e., S <- T
  std::unordered_map<B, std::unordered_set<A>> directAncestorMap;

  [[nodiscard]] std::vector<std::pair<A, B>> allRelationsToVectorFiltered(
      const std::unordered_map<A, std::unordered_set<B>>& successors,
      const std::function<bool(A)>& filterStmt1,
      const std::function<bool(B)>& filterStmt2) const {
    std::vector<std::pair<A, B>> res;
    for (const auto& [s, setT] : successors) {
      if (!filterStmt1(s)) continue;
      for (const auto& t : setT) {
        if (!filterStmt2(t)) continue;
        res.emplace_back(s, t);
      }
    }
    return res;
  }

  [[nodiscard]] std::vector<std::pair<A, B>> allRelationsToVector(
      const std::unordered_map<A, std::unordered_set<B>>& successors) const {
    std::vector<std::pair<A, B>> res;
    for (const auto& [s, setT] : successors) {
      for (const auto& t : setT) {
        res.emplace_back(s, t);
      }
    }
    return res;
  }

  template <typename K, typename V>
  [[nodiscard]] std::vector<V> relationToVectorFiltered(
      K key, const std::unordered_map<K, std::unordered_set<V>>& relationMap,
      const std::function<bool(V)>& filter) const {
    std::vector<V> res;
    auto it = relationMap.find(key);
    if (it == relationMap.end()) {
      return res;
    }
    const auto& setV = it->second;
    res.reserve(setV.size());
    std::copy_if(setV.begin(), setV.end(), std::back_inserter(res), filter);
    return res;
  }

  template <typename K, typename V>
  [[nodiscard]] std::vector<V> relationToVector(
      K key,
      const std::unordered_map<K, std::unordered_set<V>>& relationMap) const {
    std::vector<V> res;
    auto it = relationMap.find(key);
    if (it == relationMap.end()) {
      return res;
    }
    const auto& setV = it->second;
    res.reserve(setV.size());
    std::copy(setV.begin(), setV.end(), std::back_inserter(res));
    return res;
  }

 public:
  virtual ~RelationStore() = default;

  virtual void addRelation(A from, B to) {
    directSuccessorMap[from].insert(to);
    directAncestorMap[to].insert(from);
  }

  [[nodiscard]] bool hasDirectSuccessor(A from) const {
    return directSuccessorMap.count(from);
  }

  [[nodiscard]] bool hasDirectAncestor(B to) const {
    return directAncestorMap.count(to);
  }

  [[nodiscard]] const std::unordered_set<B>& getDirectSuccessors(A from) const {
    return directSuccessorMap.at(from);
  }

  [[nodiscard]] const std::unordered_set<A>& getDirectAncestors(B to) const {
    return directAncestorMap.at(to);
  }

  [[nodiscard]] bool hasDirectRelation(A from, B to) const {
    return directSuccessorMap.count(from) &&
           directSuccessorMap.at(from).count(to);
  }

  [[nodiscard]] std::vector<B> getAllDirectSuccessorsOf(A from) const {
    return relationToVector<A, B>(from, directSuccessorMap);
  }

  [[nodiscard]] std::vector<B> getDirectSuccessorsOf(
      A from, const std::function<bool(B)>& filter) const {
    return relationToVectorFiltered<A, B>(from, directSuccessorMap, filter);
  }

  [[nodiscard]] std::vector<B> getAllDirectAncestorsOf(B to) const {
    return relationToVector<A, B>(to, directAncestorMap);
  }

  [[nodiscard]] std::vector<A> getDirectAncestorsOf(
      B to, const std::function<bool(A)>& filter) const {
    return relationToVectorFiltered<B, A>(to, directAncestorMap, filter);
  }

  [[nodiscard]] std::vector<std::pair<A, B>> getDirectRelations(
      std::pair<const std::function<bool(A)>&, const std::function<bool(B)>&>
          filterStmtPair) const {
    return allRelationsToVectorFiltered(
        directSuccessorMap, filterStmtPair.first, filterStmtPair.second);
  }

  [[nodiscard]] std::vector<std::pair<A, B>> getAllDirectRelations() const {
    return allRelationsToVector(directSuccessorMap);
  }

  [[nodiscard]] std::unordered_map<A, std::unordered_set<B>>
  getDirectRelations() const {
    return directSuccessorMap;
  }

  virtual void clearCache() {}
};
