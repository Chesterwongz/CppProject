#include "CFG.h"

CFG::CFG() = default;

CFG::CFG(unordered_map<int, vector<int>> adjList,
         unordered_map<int, vector<int>> reversedAdjList) :
         adjList(std::move(adjList)), reversedAdjList(std::move(reversedAdjList)) {}

void CFG::addEdge(int from, int to) {
    adjList[from].push_back(to);
    reversedAdjList[to].push_back(from);
}

bool CFG::operator==(const CFG &other) const {
    return adjList == other.adjList && reversedAdjList == other.reversedAdjList;
}
