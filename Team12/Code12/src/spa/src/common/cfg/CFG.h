#pragma once

#include <unordered_map>
#include <vector>
#include <utility>
#include <iostream>

using std::unordered_map, std::vector;

class CFG {
private:
    unordered_map<int, vector<int>> adjList;

protected:
    explicit CFG(unordered_map<int, vector<int>> adjList);

public:
    CFG();
    void addEdge(int from, int to);
    bool operator== (const CFG& other) const;
    void printAdjList();
};
