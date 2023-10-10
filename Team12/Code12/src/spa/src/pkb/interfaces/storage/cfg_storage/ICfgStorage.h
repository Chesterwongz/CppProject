#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/cfg/CFG.h"

class ICfgStorage {
 public:
  virtual ~ICfgStorage() = default;

  virtual void addCfg(const std::string& procName,
                      std::unique_ptr<CFG> cfg) = 0;

  virtual std::vector<std::pair<int, int>> getNextPairs() = 0;

  virtual std::unordered_set<int> getNextStmts(const std::string& procName,
                                                   int stmtNum) = 0;
  virtual std::unordered_set<int> getPrevStmts(const std::string& procName,
                                                   int stmtNum) = 0;
  virtual bool isNext(const std::string& proc, int firstStmtNum,
                      int secondStmtNum) = 0;

  virtual std::vector<std::pair<int, int>> getNextTPairs() = 0;

  virtual std::unordered_set<int> getNextTStmts(const std::string& procName,
                                                    int stmtNum) = 0;

  virtual std::unordered_set<int> getPrevTStmts(const std::string& procName,
                                                    int stmtNum) = 0;

  virtual bool isNextT(const std::string& proc, int firstStmtNum,
                       int secondStmtNum) = 0;
};
