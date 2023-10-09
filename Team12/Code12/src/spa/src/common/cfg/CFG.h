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
  [[nodiscard]] unordered_set<int> getStmtsFromMap(
      const unordered_map<int, unordered_set<int>>& map, int stmtNum) const;

 protected:
  explicit CFG(unordered_map<int, unordered_set<int>> adjList,
               unordered_map<int, unordered_set<int>> reversedAdjList);

 public:
  CFG();
  void addEdge(int from, int to);
  bool operator==(const CFG& other) const;
  [[nodiscard]] unordered_set<int> getNextStmtsFrom(int stmtNum) const;
  [[nodiscard]] unordered_set<int> getPrevStmtsFrom(int stmtNum) const;
  [[nodiscard]] const unordered_map<int, unordered_set<int>>& getAdjList()
      const;
  [[nodiscard]] const unordered_map<int, unordered_set<int>>&
  getReversedAdjList() const;
};
