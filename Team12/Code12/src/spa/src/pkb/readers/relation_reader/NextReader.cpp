#include "NextReader.h"

std::vector<std::pair<std::string, std::string>> NextReader::getNextPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  std::vector<std::pair<std::string, std::string>> nextPairs;

  for (const auto& entry : cfgStorage) {
    int stmt1 = entry.first;
    const auto& successors = entry.second;

    for (int stmt2 : successors) {
      nextPairs.emplace_back(stmt1, stmt2);
    }
  }

  return nextPairs;
}

bool NextReader::isNext(int firstStmtNumber, int secondStmtNumber) {}

std::vector<std::string> NextReader::getNextFirstStmt(int secondStmtNumber,
                                                      StmtType firstStmtType) {
  return {};
};

std::vector<std::string> NextReader::getNextSecondStmt(
    int firstStmtNumber, StmtType secondStmtType) {
  return {};
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextStarPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return {};
}

bool NextReader::isNextStar(int firstStmtNumber, int secondStmtNumber) {
  return storage.isNextStar(firstStmtNumber, secondStmtNumber);
}

std::vector<std::string> NextReader::getNextStarFirstStmt(
    int secondStmtNumber, StmtType firstStmtType) {
  return {};
}

std::vector<std::string> NextReader::getNextStarSecondStmt(
    int firstStmtNumber, StmtType secondStmtType) {
  return {};
}