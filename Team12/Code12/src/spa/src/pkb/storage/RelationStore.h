#pragma once

#include <functional>
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
    std::vector<std::pair<S, T>> result;
    for (const auto& [s, setT] : successors) {
      if (!filterStmt1(s)) continue;
      for (const auto& t : setT) {
        if (!filterStmt2(t)) continue;
        result.emplace_back(s, t);
      }
    }
    return result;
  }

 public:
  /**
   * adds a relation from S to T. E.g., Follows(S,T)
   * @param from
   * @param to
   */
  virtual void addRelation(S from, T to) {
    directSuccessorMap[from].insert(to);
    directAncestorMap[to].insert(from);
  }

  [[nodiscard]] bool hasDirectSuccessor(S from) const {
    return directSuccessorMap.count(from);
  }

  [[nodiscard]] bool hasDirectAncestor(T to) const {
    return directAncestorMap.count(to);
  }

  [[nodiscard]] bool hasDirectRelation(S from, T to) const {
    return hasDirectSuccessor(from) && directSuccessorMap.at(from).count(to);
  }

  [[nodiscard]] const std::unordered_set<T>& getDirectSuccessor(S from) const {
    return directSuccessorMap.at(from);
  }

  [[nodiscard]] const std::unordered_set<S>& getDirectAncestor(T to) const {
    return directAncestorMap.at(to);
  }

  [[nodiscard]] std::vector<std::pair<S, T>> getAllRelations(
      const std::function<bool(S)>& filterStmt1,
      const std::function<bool(T)>& filterStmt2) const {
    return flatMap(directSuccessorMap, filterStmt1, filterStmt2);
  }
};
