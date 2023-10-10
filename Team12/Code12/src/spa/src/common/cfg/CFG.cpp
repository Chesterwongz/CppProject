#include "CFG.h"

#include "pkb/utils/FunctionUtils.h"

CFG::CFG() = default;

CFG::CFG(unordered_map<int, unordered_set<int>> adjList,
         unordered_map<int, unordered_set<int>> reversedAdjList)
    : adjList(std::move(adjList)),
      reversedAdjList(std::move(reversedAdjList)) {}

void CFG::addEdge(int from, int to) {
  adjList[from].insert(to);
  reversedAdjList[to].insert(from);
}

void CFG::addTransitiveEdge(int from, int to) {
  nextTCache[from].insert(to);
  prevTCache[to].insert(from);
}

bool CFG::operator==(const CFG &other) const {
  return adjList == other.adjList && reversedAdjList == other.reversedAdjList;
}

bool CFG::isNext(int firstStmtNum, int secondStmtNum) const {
  if (adjList.find(firstStmtNum) == adjList.end()) {
    return false;
  }
  unordered_set<int> nextStmtsOfFirst = adjList.at(firstStmtNum);
  return nextStmtsOfFirst.find(secondStmtNum) != nextStmtsOfFirst.end();
}

unordered_set<int> CFG::getStmtsFromMap(
    const unordered_map<int, unordered_set<int>> &map, int stmtNum) const {
  if (map.find(stmtNum) == map.end()) {
    return {};
  }
  return map.at(stmtNum);
}

unordered_set<int> CFG::getNextStmts(int stmtNum) const {
  return getStmtsFromMap(adjList, stmtNum);
}

unordered_set<int> CFG::getPrevStmts(int stmtNum) const {
  return getStmtsFromMap(reversedAdjList, stmtNum);
}

const unordered_map<int, unordered_set<int>> &CFG::getAdjList() const {
  return adjList;
}

const unordered_map<int, unordered_set<int>> &CFG::getReversedAdjList() const {
  return reversedAdjList;
}

unordered_set<int> CFG::getNextTStmts(int stmtNum) {
  unordered_set<int> nextTStmts =
      FunctionUtils<int, CFG>::computeTransitiveRelationship(
          stmtNum, &CFG::getNextStmts, nextTCache, this);
  for (int next : nextTStmts) {
    addTransitiveEdge(stmtNum, next);
  }
  return nextTStmts;
}

unordered_set<int> CFG::getPrevTStmts(int stmtNum) {
  unordered_set<int> prevTStmts =
      FunctionUtils<int, CFG>::computeTransitiveRelationship(
          stmtNum, &CFG::getPrevStmts, prevTCache, this);
  for (int prev : prevTStmts) {
    addTransitiveEdge(prev, stmtNum);
  }
  return prevTStmts;
}
