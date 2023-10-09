#pragma once

#include <string>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"

class INextReader {
 public:
  virtual ~INextReader() = default;
  virtual std::vector<std::pair<std::string, std::string>> getNextPairs(
      StmtType firstStmtType, StmtType secondStmtType) = 0;

  virtual bool isNext(int firstStmtNumber, int secondStmtNumber) = 0;

  virtual std::vector<std::string> getNextFirstStmt(int secondStmtNumber,
                                                    StmtType firstStmtType) = 0;

  virtual std::vector<std::string> getNextSecondStmt(
      int firstStmtNumber, StmtType secondStmtType) = 0;

  virtual std::vector<std::pair<std::string, std::string>> getNextStarPairs(
      StmtType firstStmtType, StmtType secondStmtType) = 0;

  virtual bool isNextStar(int firstStmtNumber, int secondStmtNumber) = 0;

  virtual std::vector<std::string> getNextStarFirstStmt(
      int secondStmtNumber, StmtType firstStmtType) = 0;

  virtual std::vector<std::string> getNextStarSecondStmt(
      int firstStmtNumber, StmtType secondStmtType) = 0;
};
