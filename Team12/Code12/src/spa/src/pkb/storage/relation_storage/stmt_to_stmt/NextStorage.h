#pragma once

#include <memory>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/AliasTypes.h"
#include "common/Constants.h"
#include "common/cfg/CFG.h"
#include "pkb/interfaces/storage/relation_storage/INextStorage.h"
#include "pkb/utils/FunctionUtils.h"

class NextStorage : public INextStorage {
 private:
  IntToIntSetMap nextStmts;
  IntToIntSetMap prevStmts;
  IntToIntSetMap nextTCache;
  IntToIntSetMap prevTCache;
  void addNextT(int from, int to);

 public:
  NextStorage();
  void addNext(int from, int to) override;
  void addNext(const std::unique_ptr<CFG>& cfg);
  IntSet getNextStmts(int stmtNum) override;
  IntSet getPrevStmts(int stmtNum) override;
  IntSet getNextTStmts(int stmtNum) override;
  IntSet getPrevTStmts(int stmtNum) override;
  bool isNext(int firstStmtNum, int secondStmtNum) override;
  bool isNextT(int firstStmtNum, int secondStmtNum) override;
  std::vector<std::pair<int, int>> getNextPairs() override;
  std::vector<std::pair<int, int>> getNextTPairs() override;
};
