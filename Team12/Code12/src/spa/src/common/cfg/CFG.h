#pragma once

#include <unordered_map>
#include <vector>

using std::unordered_map, std::vector;

class CFG {
private:
    unordered_map<int, vector<int>> adjList;

public:
    CFG();
    void addEdge(int from, int to);
};
