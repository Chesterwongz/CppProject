#include "NextStorage.h"

NextStorage::NextStorage() = default;

void NextStorage::addNext(int from, int to) {
  nextStmts[from].insert(to);
  prevStmts[to].insert(from);
}

void NextStorage::addNext(const std::unique_ptr<CFG>& cfg) {
  for (const auto& [from, toSet] : cfg->getAdjList()) {
    for (int to : toSet) {
      addNext(from, to);
    }
  }
}

void NextStorage::addNextT(int from, int to) {
  nextTCache[from].insert(to);
  prevTCache[to].insert(from);
}

IntSet NextStorage::getStmts(IntToIntSetMap& map, int stmtNum) {
  if (map.find(stmtNum) == map.end()) {
    return {};
  }
  return map.at(stmtNum);
}

IntSet NextStorage::getNextStmts(int stmtNum) {
  return getStmts(nextStmts, stmtNum);
}

IntSet NextStorage::getPrevStmts(int stmtNum) {
  return getStmts(prevStmts, stmtNum);
}

IntSet NextStorage::getNextTStmts(int stmtNum) {
  auto lambdaGetNextStmts = [this](int s) { return this->getNextStmts(s); };
  IntSet nextTStmts = FunctionUtils<int, decltype(lambdaGetNextStmts)>::
      computeTransitiveRelationship(stmtNum, lambdaGetNextStmts);
  for (int next : nextTStmts) {
    addNextT(stmtNum, next);
  }
  return nextTStmts;
}

IntSet NextStorage::getPrevTStmts(int stmtNum) {
  auto lambdaGetPrevStmts = [this](int s) { return this->getPrevStmts(s); };
  IntSet prevTStmts = FunctionUtils<int, decltype(lambdaGetPrevStmts)>::
      computeTransitiveRelationship(stmtNum, lambdaGetPrevStmts);
  for (int prev : prevTStmts) {
    addNextT(prev, stmtNum);
  }
  return prevTStmts;
}

bool NextStorage::isNext(int firstStmtNum, int secondStmtNum) {
  if (nextStmts.find(firstStmtNum) == nextStmts.end()) {
    return false;
  }
  IntSet nextStmtsOfFirst = nextStmts.at(firstStmtNum);
  return nextStmtsOfFirst.find(secondStmtNum) != nextStmtsOfFirst.end();
}

bool NextStorage::isNextT(int firstStmtNum, int secondStmtNum) {
  if (nextStmts.find(firstStmtNum) == nextStmts.end()) {
    return false;
  }
  IntSet nextTStmtsOfFirst = getNextTStmts(firstStmtNum);
  return nextTStmtsOfFirst.find(secondStmtNum) != nextTStmtsOfFirst.end();
}

std::vector<std::pair<int, int>> NextStorage::getNextPairs() {
  std::vector<std::pair<int, int>> nextPairs;
  for (const auto& [from, toSet] : nextStmts) {
    for (int to : toSet) {
      nextPairs.emplace_back(from, to);
    }
  }
  return nextPairs;
}

void NextStorage::clearCache() {
  nextTCache.clear();
  prevTCache.clear();
}
