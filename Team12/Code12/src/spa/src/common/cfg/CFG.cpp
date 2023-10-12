#include "CFG.h"

CFG::CFG() = default;

CFG::CFG(IntToIntSetMap adjList)
    : adjList(std::move(adjList)) {}

void CFG::addEdge(int from, int to) {
  adjList[from].insert(to);
}

bool CFG::operator==(const CFG& other) const {
  return adjList == other.adjList;
}

const IntToIntSetMap& CFG::getAdjList() const { return adjList; }
