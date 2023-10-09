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

unordered_set<int> CFG::getNextStmtFrom(int stmtNum) const {
  if (adjList.find(stmtNum) == adjList.end()) {
    return {};
  }
  return adjList.at(stmtNum);
}

unordered_set<int> CFG::getPrevStmtFrom(int stmtNum) const {
  if (reversedAdjList.find(stmtNum) == reversedAdjList.end()) {
    return {};
  }
  return reversedAdjList.at(stmtNum);
}

const unordered_map<int, unordered_set<int>> &CFG::getAdjList() const {
  return adjList;
}

const unordered_map<int, unordered_set<int>> &CFG::getReversedAdjList() const {
  return reversedAdjList;
}
