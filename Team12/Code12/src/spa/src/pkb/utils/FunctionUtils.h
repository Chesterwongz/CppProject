#pragma once

#include <stack>
#include <unordered_map>
#include <unordered_set>

using std::stack, std::unordered_map, std::unordered_set;

template <typename ElementType, typename ClassType>
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
      unordered_set<ElementType> (ClassType::*)(ElementType) const;

  static unordered_set<ElementType> computeTransitiveRelationship(
      ElementType element, NeighborFunction getNeighbor,
      unordered_map<ElementType, unordered_set<ElementType>>& cache,
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

      unordered_set<ElementType> nbrsOfCurr = cache[curr];
      if (!nbrsOfCurr.empty()) {
        visited.insert(nbrsOfCurr.begin(), nbrsOfCurr.end());
      } else {
        unordered_set<ElementType> directNbrs = (instance->*getNeighbor)(curr);
        addToVisit(visited, toVisit, directNbrs);
      }
    }

    cache[element] = visited;
    return visited;
  }
};
