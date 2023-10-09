#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

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
  bool operator==(const CFG& other) const;
  unordered_set<int> getNextStmtFrom(int stmtNum) const;
  unordered_set<int> getPrevStmtFrom(int stmtNum) const;
  const unordered_map<int, unordered_set<int>>& getAdjList() const;
  const unordered_map<int, unordered_set<int>>& getReversedAdjList() const;
};
