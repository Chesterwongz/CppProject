#include "CFG.h"

CFG::CFG() = default;

CFG::CFG(IntToIntSetMap adjList, IntToIntSetMap reversedAdjList)
    : adjList(std::move(adjList)),
      reversedAdjList(std::move(reversedAdjList)) {}

void CFG::addEdge(int from, int to) {
  adjList[from].insert(to);
  reversedAdjList[to].insert(from);
}

bool CFG::operator==(const CFG& other) const {
  return adjList == other.adjList && reversedAdjList == other.reversedAdjList;
}

const IntToIntSetMap& CFG::getAdjList() const { return adjList; }
