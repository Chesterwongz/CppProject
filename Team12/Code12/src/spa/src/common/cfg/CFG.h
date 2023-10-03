#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <iostream>

using std::unordered_map, std::unordered_set;

class CFG {
private:
    unordered_map<int, unordered_set<int>> adjList;
    unordered_map<int, unordered_set<int>> reversedAdjList;

protected:
    explicit CFG(unordered_map<int, unordered_set<int>> adjList,
                 unordered_map<int, unordered_set<int>> reversedAdjList);

public:
    CFG();
    void addEdge(int from, int to);
    bool operator== (const CFG& other) const;
};
