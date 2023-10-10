#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/Constants.h"
#include "pkb/interfaces/storage/cfg_storage/ICfgStorage.h"

class CfgStorage : public ICfgStorage {
 private:
  std::unordered_map<std::string, std::unique_ptr<CFG>> procToCfgMap;
  std::unordered_set<int> getStmtsFrom(
      std::unordered_set<int> (CFG::*cfgFunction)(int) const,
      const std::string& procName, int stmtNum);
  void addNextPairForCfg(
      const std::unique_ptr<CFG>& cfg,
      std::vector<std::pair<int, int>>& nextPairs);

 public:
  void addCfg(const std::string& procName, std::unique_ptr<CFG> cfg) override;

  std::vector<std::pair<int, int>> getNextPairs() override;

  unordered_set<int> getNextStmtsFrom(const std::string& procName,
                                      int stmtNum) override;
  unordered_set<int> getPrevStmtsFrom(const std::string& procName,
                                      int stmtNum) override;

  bool isNext(const std::string& proc, int firstStmtNum,
              int secondStmtNum) override;
};
