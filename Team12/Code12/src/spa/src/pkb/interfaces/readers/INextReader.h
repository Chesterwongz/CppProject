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

  virtual std::vector<std::string> getPrevStmts(int s2, StmtType type1) = 0;
  virtual std::vector<std::string> getPrevTStmts(int s2, StmtType type1) = 0;

  virtual std::vector<std::string> getNextStmts(int s1, StmtType type2) = 0;
  virtual std::vector<std::string> getNextTStmts(int s1, StmtType type2) = 0;
};
