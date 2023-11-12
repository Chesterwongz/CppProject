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

  virtual std::vector<std::string> getPrevStmts(StmtType type1, int s2) = 0;
  virtual std::vector<std::string> getPrevTStmts(StmtType type1, int s2) = 0;

  virtual std::vector<std::string> getNextStmts(StmtType type2, int s1) = 0;
  virtual std::vector<std::string> getNextTStmts(StmtType type2, int s1) = 0;
};
