#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename S, typename T>
class RelationStore {
 protected:
  // An unordered set of the direct successors of S. I.e., S -> T
  std::unordered_map<S, std::unordered_set<T>> directSuccessorMap;

  // An unordered set of the direct ancestors of S. I.e., S <- T
  std::unordered_map<T, std::unordered_set<S>> directAncestorMap;

  [[nodiscard]] std::vector<std::pair<S, T>> flatMap(
      const std::unordered_map<S, std::unordered_set<T>>& successors,
      const std::function<bool(S)>& filterStmt1,
      const std::function<bool(T)>& filterStmt2) const {
    std::vector<std::pair<S, T>> res;
    for (const auto& [s, setT] : successors) {
      if (!filterStmt1(s)) continue;
      for (const auto& t : setT) {
        if (!filterStmt2(t)) continue;
        res.emplace_back(s, t);
      }
    }
    return res;
  }

  template <typename K, typename V>
  [[nodiscard]] std::vector<V> map(
      K key, const std::unordered_map<K, std::unordered_set<V>>& relationMap,
      const std::function<bool(V)>& filter) const {
    std::vector<V> res;
    auto it = relationMap.find(key);
    if (it == relationMap.end()) {
      return res;
    }
    const auto& setV = it->second;
    std::copy_if(setV.begin(), setV.end(), std::back_inserter(res), filter);
    return res;
  }

 public:
  virtual void addRelation(S from, T to) {
    directSuccessorMap[from].insert(to);
    directAncestorMap[to].insert(from);
  }

  [[nodiscard]] bool hasDirectRelation(S from, T to) const {
    return directSuccessorMap.count(from) &&
           directSuccessorMap.at(from).count(to);
  }

  [[nodiscard]] std::vector<T> getDirectSuccessor(
      S from, const std::function<bool(T)>& filter) const {
    return map<S, T>(from, directSuccessorMap, filter);
  }

  [[nodiscard]] std::vector<S> getDirectAncestor(
      T to, const std::function<bool(S)>& filter) const {
    return map<T, S>(to, directAncestorMap, filter);
  }

  [[nodiscard]] std::vector<std::pair<S, T>> getAllRelations(
      std::pair<const std::function<bool(S)>&, const std::function<bool(T)>&>
          filterStmtPair) const {
    return flatMap(directSuccessorMap, filterStmtPair.first,
                   filterStmtPair.second);
  }
};
