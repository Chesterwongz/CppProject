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

 public:
  virtual ~RelationStore() = default;

  virtual void addRelation(A from, B to) {
    directSuccessorMap[from].insert(to);
    directAncestorMap[to].insert(from);
  }

  [[nodiscard]] bool hasDirectSuccessors(A from) const {
    return directSuccessorMap.count(from);
  }

  [[nodiscard]] const std::unordered_set<B>& getDirectSuccessors(A from) const {
    return directSuccessorMap.at(from);
  }

  [[nodiscard]] bool hasDirectAncestors(B to) const {
    return directAncestorMap.count(to);
  }

  [[nodiscard]] const std::unordered_set<A>& getDirectAncestors(B to) const {
    return directAncestorMap.at(to);
  }

  [[nodiscard]] bool hasDirectRelation(A from, B to) const {
    return directSuccessorMap.count(from) &&
           directSuccessorMap.at(from).count(to);
  }

  [[nodiscard]] const std::unordered_map<A, std::unordered_set<B>>&
  getDirectRelations() const {
    return directSuccessorMap;
  }

  [[nodiscard]] const std::unordered_map<B, std::unordered_set<A>>&
  getDirectBackwardRelations() const {
    return directAncestorMap;
  }

  virtual void clearCache() {}
};
