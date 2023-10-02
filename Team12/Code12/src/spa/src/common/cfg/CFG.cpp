#include "CFG.h"

CFG::CFG() = default;

CFG::CFG(unordered_map<int, vector<int>> adjList) : adjList(std::move(adjList)) {}

void CFG::addEdge(int from, int to) {
    adjList[from].push_back(to);
}

bool CFG::operator==(const CFG &other) const {
    return adjList == other.adjList;
}
