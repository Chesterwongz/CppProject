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
  virtual std::vector<std::pair<std::string, std::string>> getNextTPairs(
      StmtType firstStmtType, StmtType secondStmtType) = 0;

  virtual bool isNext(int firstStmtNum, int secondStmtNum) = 0;
  virtual bool isNextT(int firstStmtNum, int secondStmtNum) = 0;

  virtual std::vector<std::string> getPrevStmts(int secondStmtNum,
                                                StmtType firstStmtType) = 0;
  virtual std::vector<std::string> getPrevTStmts(int secondStmtNum,
                                                 StmtType firstStmtType) = 0;

  virtual std::vector<std::string> getNextStmts(int firstStmtNum,
                                                StmtType secondStmtType) = 0;
  virtual std::vector<std::string> getNextTStmts(int firstStmtNum,
                                                 StmtType secondStmtType) = 0;
};
