#include "NextReader.h"

std::vector<std::pair<std::string, std::string>> NextReader::getNextPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return cfgStorage.getNextPairs();
}

bool NextReader::isNext(int firstStmtNum, int secondStmtNum) {
  std::string proc1 = entityStorage.getProcFromStmt(firstStmtNum);
  std::string proc2 = entityStorage.getProcFromStmt(secondStmtNum);
  if (proc1 == common::INVALID_PROC_NAME ||
      proc2 == common::INVALID_PROC_NAME || proc1 != proc2) {
    return false;
  }
  return cfgStorage.isNext(proc1, firstStmtNum, secondStmtNum);
}

std::vector<std::string> NextReader::getStmtsFrom(GetStmtsFunction getStmtsFunc,
                                                  int stmtNum, StmtType type) {
  std::string proc = entityStorage.getProcFromStmt(stmtNum);
  if (proc == common::INVALID_PROC_NAME) {
    return {};
  }
  const auto& stmtNums = (cfgStorage.*getStmtsFunc)(proc, stmtNum);
  std::vector<std::string> stmts;
  for (int num : stmtNums) {
    if (stmtStorage.isStatementType(num, type)) {
      stmts.emplace_back(std::to_string(num));
    }
  }
  return stmts;
}

std::vector<std::string> NextReader::getPrevStmtsFrom(int secondStmtNum,
                                                      StmtType firstStmtType) {
  return getStmtsFrom(&ICfgStorage::getPrevStmtsFrom, secondStmtNum,
                      firstStmtType);
}

std::vector<std::string> NextReader::getNextStmtsFrom(int firstStmtNum,
                                                      StmtType secondStmtType) {
  return getStmtsFrom(&ICfgStorage::getNextStmtsFrom, firstStmtNum,
                      secondStmtType);
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextStarPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return {};
}

bool NextReader::isNextStar(int firstStmtNum, int secondStmtNum) {
  return false;
}

std::vector<std::string> NextReader::getNextStarFirstStmt(
    int secondStmtNum, StmtType firstStmtType) {
  return {};
}

std::vector<std::string> NextReader::getNextStarSecondStmt(
    int firstStmtNum, StmtType secondStmtType) {
  return {};
}
