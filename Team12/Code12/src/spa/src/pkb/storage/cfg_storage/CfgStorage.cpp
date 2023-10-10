#include "CfgStorage.h"

void CfgStorage::addCfg(const std::string& procName, std::unique_ptr<CFG> cfg) {
  procToCfgMap[procName] = std::move(cfg);
}

void CfgStorage::addNextPairForCfg(
    const std::unique_ptr<CFG>& cfg,
    std::vector<std::pair<int, int>>& nextPairs) {
  for (const auto& [firstStmtNum, secondStmtNums] : cfg->getAdjList()) {
    for (const auto& secondStmtNum : secondStmtNums) {
      if (secondStmtNum == common::INVALID_STMT_NUM) {
        continue;
      }
      nextPairs.emplace_back(firstStmtNum, secondStmtNum);
    }
  }
}

std::vector<std::pair<int, int>> CfgStorage::getNextPairs() {
  std::vector<std::pair<int, int>> nextPairs;
  for (const auto& [procName, cfg] : procToCfgMap) {
    addNextPairForCfg(cfg, nextPairs);
  }
  return nextPairs;
}

std::unordered_set<int> CfgStorage::getStmtsFrom(
    std::unordered_set<int> (CFG::*cfgFunction)(int) const,
    const std::string& procName, int stmtNum) {
  if (procToCfgMap.find(procName) == procToCfgMap.end()) {
    return {};
  }
  const CFG& procCfg = *procToCfgMap.at(procName);
  return (procCfg.*cfgFunction)(stmtNum);
}

std::unordered_set<int> CfgStorage::getNextStmts(const std::string& procName,
                                                 int stmtNum) {
  return getStmtsFrom(&CFG::getNextStmts, procName, stmtNum);
}

std::unordered_set<int> CfgStorage::getPrevStmts(const std::string& procName,
                                                 int stmtNum) {
  return getStmtsFrom(&CFG::getPrevStmts, procName, stmtNum);
}

bool CfgStorage::isNext(const std::string& proc, int firstStmtNum,
                        int secondStmtNum) {
  if (procToCfgMap.find(proc) == procToCfgMap.end()) {
    return false;
  }
  return procToCfgMap[proc]->isNext(firstStmtNum, secondStmtNum);
}
std::unordered_set<int> CfgStorage::getNextTStmts(const std::string& procName,
                                                  int stmtNum) {
  return std::unordered_set<int>();
}
std::unordered_set<int> CfgStorage::getPrevTStmts(const std::string& procName,
                                                  int stmtNum) {
  return std::unordered_set<int>();
}
std::vector<std::pair<int, int>> CfgStorage::getNextTPairs() {
  return std::vector<std::pair<int, int>>();
}
bool CfgStorage::isNextT(const std::string& proc, int firstStmtNum,
                         int secondStmtNum) {
  return false;
}
