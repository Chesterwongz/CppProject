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

unordered_set<int> CFG::getNextStmtsFrom(int stmtNum) {
  return getStmtsFromMap(adjList, stmtNum);
}

unordered_set<int> CFG::getPrevStmtsFrom(int stmtNum) {
  return getStmtsFromMap(reversedAdjList, stmtNum);
}

const unordered_map<int, unordered_set<int>> &CFG::getAdjList() const {
  return adjList;
}

const unordered_map<int, unordered_set<int>> &CFG::getReversedAdjList() const {
  return reversedAdjList;
}

unordered_set<int> CFG::getNextStarStmtFrom(int stmtNum) {
  unordered_set<int> nextStarStmts =
      FunctionUtils<int, CFG>::computeTransitiveRelationship(
          stmtNum, &CFG::getNextStmtsFrom, cacheNextStar, this);
  // TODO(Xiaoyun): update add transitive edges
  cacheNextStar[stmtNum] = nextStarStmts;
  return nextStarStmts;
}

unordered_set<int> CFG::getPrevStarStmtFrom(int stmtNum) {
  unordered_set<int> prevStarStmts =
      FunctionUtils<int, CFG>::computeTransitiveRelationship(
          stmtNum, &CFG::getPrevStmtsFrom, cachePrevStar, this);
  cachePrevStar[stmtNum] = prevStarStmts;
  return prevStarStmts;
}
