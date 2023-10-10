#include "NextReader.h"

std::vector<std::pair<std::string, std::string>> NextReader::getNextPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  std::vector<std::pair<int, int>> allNextPairs = cfgStorage.getNextPairs();
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
    if (num != common::INVALID_STMT_NUM &&
        stmtStorage.isStatementType(num, type)) {
      stmts.emplace_back(std::to_string(num));
    }
  }
  return stmts;
}

std::vector<std::string> NextReader::getPrevStmts(int secondStmtNum,
                                                  StmtType firstStmtType) {
  return getStmtsFrom(&ICfgStorage::getPrevStmts, secondStmtNum, firstStmtType);
}

std::vector<std::string> NextReader::getNextStmts(int firstStmtNum,
                                                  StmtType secondStmtType) {
  return getStmtsFrom(&ICfgStorage::getNextStmts, firstStmtNum, secondStmtType);
}

std::vector<std::string> NextReader::getPrevTStmts(int stmtNum,
                                                   StmtType firstStmtType) {
  std::string proc = entityStorage.getProcFromStmt(stmtNum);
  if (proc == common::INVALID_PROC_NAME) {
    return {};
  }
  return {};
}

std::vector<std::string> NextReader::getNextTStmts(int firstStmtNumber,
                                                   StmtType secondStmtType) {
  return {};
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextTPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return {};
}

bool NextReader::isNextT(int firstStmtNum, int secondStmtNum) { return false; }
