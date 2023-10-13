#pragma once

#include <stack>
#include <unordered_map>
#include <unordered_set>

using std::stack, std::unordered_map, std::unordered_set;

// ai-gen start(gpt-4, 2)
template <typename ElementType, typename FuncType,
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
  static unordered_set<ElementType> computeTransitiveRelationship(
      ArgType element, FuncType getNeighbor,
      const unordered_map<ElementType, unordered_set<ElementType>>* cache =
          nullptr) {
    if (cache && cache->find(element) != cache->end()) {
      return cache->at(element);
    }
    unordered_set<ElementType> visited;
    stack<ElementType> toVisit;
    for (ElementType s : getNeighbor(element)) {
      toVisit.push(s);
    }
    while (!toVisit.empty()) {
      ElementType curr = toVisit.top();
      toVisit.pop();
      visited.insert(curr);

      if (cache && cache->find(curr) != cache->end()) {
        unordered_set<ElementType> nbrsOfCurr = cache->at(curr);
        visited.insert(nbrsOfCurr.begin(), nbrsOfCurr.end());
      } else {
        unordered_set<ElementType> directNbrs = getNeighbor(curr);
        addToVisit(visited, toVisit, directNbrs);
      }
    }
    return visited;
  }
};
// ai-gen end(gpt-4, 2)
