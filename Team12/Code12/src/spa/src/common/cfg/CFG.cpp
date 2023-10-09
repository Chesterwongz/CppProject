#include "CFG.h"

CFG::CFG() = default;

CFG::CFG(unordered_map<int, unordered_set<int>> adjList,
         unordered_map<int, unordered_set<int>> reversedAdjList)
    : adjList(std::move(adjList)),
      reversedAdjList(std::move(reversedAdjList)) {}

void CFG::addEdge(int from, int to) {
  adjList[from].insert(to);
  reversedAdjList[to].insert(from);
}

bool CFG::operator==(const CFG &other) const {
  return adjList == other.adjList && reversedAdjList == other.reversedAdjList;
}

unordered_set<int> CFG::getStmtsFromMap(
    const unordered_map<int, unordered_set<int>> &map, int stmtNum) const {
  if (map.find(stmtNum) == map.end()) {
    return {};
  }
  return map.at(stmtNum);
}

unordered_set<int> CFG::getNextStmtsFrom(int stmtNum) const {
  return getStmtsFromMap(adjList, stmtNum);
}

unordered_set<int> CFG::getPrevStmtsFrom(int stmtNum) const {
  return getStmtsFromMap(reversedAdjList, stmtNum);
}

const unordered_map<int, unordered_set<int>> &CFG::getAdjList() const {
  return adjList;
}

const unordered_map<int, unordered_set<int>> &CFG::getReversedAdjList() const {
  return reversedAdjList;
}
