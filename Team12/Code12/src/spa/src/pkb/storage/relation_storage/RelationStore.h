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

  [[nodiscard]] std::unordered_set<B> getDirectSuccessors() const {
    std::unordered_set<B> result;
    result.reserve(directAncestorMap.size());
    std::transform(directAncestorMap.begin(), directAncestorMap.end(),
                   std::inserter(result, result.end()),
                   [](const auto& pair) { return pair.first; });
    return result;
  }

  [[nodiscard]] bool hasDirectAncestors(B to) const {
    return directAncestorMap.count(to);
  }

  [[nodiscard]] const std::unordered_set<A>& getDirectAncestors(B to) const {
    return directAncestorMap.at(to);
  }

  [[nodiscard]] std::unordered_set<A> getDirectAncestors() const {
    std::unordered_set<A> result;
    result.reserve(directSuccessorMap.size());
    std::transform(directSuccessorMap.begin(), directSuccessorMap.end(),
                   std::inserter(result, result.end()),
                   [](const auto& pair) { return pair.first; });
    return result;
  }

  [[nodiscard]] bool hasDirectRelation(A from, B to) const {
    return directSuccessorMap.count(from) &&
           directSuccessorMap.at(from).count(to);
  }

  [[nodiscard]] const std::unordered_map<A, std::unordered_set<B>>&
  getDirectSuccessorMap() const {
    return directSuccessorMap;
  }

  virtual void clearCache() {}
};
