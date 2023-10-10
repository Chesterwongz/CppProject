#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/AliasTypes.h"
#include "common/Constants.h"
#include "pkb/interfaces/storage/cfg_storage/ICfgStorage.h"

class CfgStorage : public ICfgStorage {
 private:
  std::unordered_map<std::string, std::unique_ptr<CFG>> procToCfgMap;
  IntSet getStmtsFrom(const IntToIntSetMap& (CFG::*cfgFunction)() const,
                      const std::string& procName, int stmtNum);
  void addNextPairForCfg(const std::unique_ptr<CFG>& cfg,
                         std::vector<std::pair<int, int>>& nextPairs);
  IntToIntSetMap nextTCache;
  IntToIntSetMap prevTCache;

 public:
  void addCfg(const std::string& procName, std::unique_ptr<CFG> cfg) override;

  std::vector<std::pair<int, int>> getNextPairs() override;

  IntSet getNextStmts(const std::string& procName, int stmtNum) override;
  IntSet getPrevStmts(const std::string& procName, int stmtNum) override;

  bool isNext(const std::string& proc, int firstStmtNum,
              int secondStmtNum) override;

  std::vector<std::pair<int, int>> getNextTPairs() override;

  IntSet getNextTStmts(const std::string& procName, int stmtNum) override;

  IntSet getPrevTStmts(const std::string& procName, int stmtNum) override;

  bool isNextT(const std::string& proc, int firstStmtNum,
               int secondStmtNum) override;
};
