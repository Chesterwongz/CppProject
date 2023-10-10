#pragma once

#include <stack>
#include <unordered_map>
#include <unordered_set>

using std::stack, std::unordered_map, std::unordered_set;

// ai-gen start(gpt-4, 1)
template <typename ElementType, typename ClassType,
          typename ArgType = ElementType>
class FunctionUtils {
 private:
  static void addToVisit(const unordered_set<ElementType>& visited,
                         stack<ElementType>& toVisit,
                         const unordered_set<ElementType>& directNbrs) {
    for (ElementType neighbor : directNbrs) {
      if (visited.find(neighbor) == visited.end()) {
        toVisit.push(neighbor);
      }
    }
  }

 public:
  using NeighborFunction =
      unordered_set<ElementType> (ClassType::*)(ArgType) const;

  static unordered_set<ElementType> computeTransitiveRelationship(
      ArgType element, NeighborFunction getNeighbor,
      const unordered_map<ElementType, unordered_set<ElementType>>& cache,
      ClassType* instance) {
    if (cache.find(element) != cache.end()) {
      return cache.at(element);
    }
    unordered_set<ElementType> visited;
    stack<ElementType> toVisit;
    for (ElementType s : (instance->*getNeighbor)(element)) {
      toVisit.push(s);
    }
    while (!toVisit.empty()) {
      ElementType curr = toVisit.top();
      toVisit.pop();
      visited.insert(curr);
      if (cache.find(element) == cache.end()) {
        unordered_set<ElementType> directNbrs = (instance->*getNeighbor)(curr);
        addToVisit(visited, toVisit, directNbrs);
      } else {
        unordered_set<ElementType> nbrsOfCurr = cache.at(curr);
        visited.insert(nbrsOfCurr.begin(), nbrsOfCurr.end());
      }
    }
    return visited;
  }
};
// ai-gen end
