#include "CFG.h"

CFG::CFG() = default;

CFG::CFG(unordered_map<int, unordered_set<int>> adjList,
         unordered_map<int, unordered_set<int>> reversedAdjList) :
         adjList(std::move(adjList)), reversedAdjList(std::move(reversedAdjList)) {}

void CFG::addEdge(int from, int to) {
    adjList[from].insert(to);
    reversedAdjList[to].insert(from);
}

bool CFG::operator==(const CFG &other) const {
    return adjList == other.adjList && reversedAdjList == other.reversedAdjList;
}
