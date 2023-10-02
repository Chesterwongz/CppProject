#include "CFG.h"

CFG::CFG() = default;

void CFG::addEdge(int from, int to) {
    adjList[from].push_back(to);
}

