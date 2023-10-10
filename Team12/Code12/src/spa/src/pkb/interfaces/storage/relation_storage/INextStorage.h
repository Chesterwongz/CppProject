#pragma once

#include <utility>
#include <vector>

#include "common/AliasTypes.h"

class INextStorage {
 public:
  virtual ~INextStorage() = default;
  virtual void addNext(int from, int to) = 0;
  virtual IntSet getNextStmts(int stmtNum) = 0;
  virtual IntSet getPrevStmts(int stmtNum) = 0;
  virtual IntSet getNextTStmts(int stmtNum) = 0;
  virtual IntSet getPrevTStmts(int stmtNum) = 0;
  virtual bool isNext(int firstStmtNum, int secondStmtNum) = 0;
  virtual bool isNextT(int firstStmtNum, int secondStmtNum) = 0;
  virtual std::vector<std::pair<int, int>> getNextPairs() = 0;
  virtual std::vector<std::pair<int, int>> getNextTPairs() = 0;
};
