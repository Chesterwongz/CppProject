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
  unordered_map<int, unordered_set<int>> nextTCache;
  unordered_map<int, unordered_set<int>> prevTCache;
  void addTransitiveEdge(int from, int to);

 protected:
  explicit CFG(unordered_map<int, unordered_set<int>> adjList,
               unordered_map<int, unordered_set<int>> reversedAdjList);

 public:
  CFG();
  void addEdge(int from, int to);
  bool operator==(const CFG& other) const;
  [[nodiscard]] unordered_set<int> getNextStmts(int stmtNum) const;
  [[nodiscard]] unordered_set<int> getPrevStmts(int stmtNum) const;
  [[nodiscard]] bool isNext(int firstStmtNum, int secondStmtNum) const;
  [[nodiscard]] const unordered_map<int, unordered_set<int>>& getAdjList()
      const;
  [[nodiscard]] const unordered_map<int, unordered_set<int>>&
  getReversedAdjList() const;
  unordered_set<int> getNextTStmts(int stmtNum);
  unordered_set<int> getPrevTStmts(int stmtNum);
};
