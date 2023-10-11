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

IntSet NextStorage::getNextStmts(int stmtNum) {
  if (nextStmts.find(stmtNum) == nextStmts.end()) {
    return {};
  }
  return nextStmts.at(stmtNum);
}

IntSet NextStorage::getPrevStmts(int stmtNum) {
  if (prevStmts.find(stmtNum) == prevStmts.end()) {
    return {};
  }
  return prevStmts.at(stmtNum);
}

IntSet NextStorage::getNextTStmts(int stmtNum) {
  IntSet nextTStmts =
      FunctionUtils<int, NextStorage>::computeTransitiveRelationship(
          stmtNum, &NextStorage::getNextStmts, this);
  for (int next : nextTStmts) {
    addNextT(stmtNum, next);
  }
  return nextTStmts;
}

IntSet NextStorage::getPrevTStmts(int stmtNum) {
  IntSet prevTStmts =
      FunctionUtils<int, NextStorage>::computeTransitiveRelationship(
          stmtNum, &NextStorage::getPrevStmts, this);
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
