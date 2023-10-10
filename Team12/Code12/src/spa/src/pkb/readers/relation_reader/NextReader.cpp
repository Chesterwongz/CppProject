#include "NextReader.h"

std::vector<std::pair<std::string, std::string>> NextReader::getNextPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  std::vector<std::pair<int, int>> allNextPairs = nextStorage.getNextPairs();
  std::vector<std::pair<std::string, std::string>> result;
  for (const auto& [first, second] : allNextPairs) {
    bool isFirstStmtRightType =
        stmtStorage.isStatementType(first, firstStmtType);
    bool isSecondStmtRightType =
        stmtStorage.isStatementType(second, secondStmtType);
    if (isFirstStmtRightType && isSecondStmtRightType) {
      result.emplace_back(std::to_string(first), std::to_string(second));
    }
  }
  return result;
}

bool NextReader::isNext(int firstStmtNum, int secondStmtNum) {
  return nextStorage.isNext(firstStmtNum, secondStmtNum);
}

std::vector<std::string> NextReader::getStmtsFrom(GetStmtsFunction getStmtsFunc,
                                                  int stmtNum, StmtType type) {
  const IntSet& stmtNums = (nextStorage.*getStmtsFunc)(stmtNum);
  std::vector<std::string> stmts;
  for (int num : stmtNums) {
    if (num != common::INVALID_STMT_NUM &&
        stmtStorage.isStatementType(num, type)) {
      stmts.emplace_back(std::to_string(num));
    }
  }
  return stmts;
}

std::vector<std::string> NextReader::getPrevStmts(int secondStmtNum,
                                                  StmtType firstStmtType) {
  return getStmtsFrom(&INextStorage::getPrevStmts, secondStmtNum,
                      firstStmtType);
}

std::vector<std::string> NextReader::getNextStmts(int firstStmtNum,
                                                  StmtType secondStmtType) {
  return getStmtsFrom(&INextStorage::getNextStmts, firstStmtNum,
                      secondStmtType);
}

std::vector<std::string> NextReader::getPrevTStmts(int stmtNum,
                                                   StmtType firstStmtType) {
  return getStmtsFrom(&INextStorage::getPrevTStmts, stmtNum, firstStmtType);
}

std::vector<std::string> NextReader::getNextTStmts(int firstStmtNumber,
                                                   StmtType secondStmtType) {
  return getStmtsFrom(&INextStorage::getNextTStmts, firstStmtNumber,
                      secondStmtType);
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextTPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  std::set<int> stmtsOfFirstType =
      stmtStorage.getStatementNumbersFromStatementType(firstStmtType);
  std::set<int> stmtsOfSecondType =
      stmtStorage.getStatementNumbersFromStatementType(secondStmtType);

  std::vector<std::pair<std::string, std::string>> result;
  for (int first : stmtsOfFirstType) {
    for (int second : stmtsOfSecondType) {
      if (nextStorage.isNextT(first, second)) {
        result.emplace_back(std::to_string(first), std::to_string(second));
      }
    }
  }
  return result;
}

bool NextReader::isNextT(int firstStmtNum, int secondStmtNum) { return false; }
