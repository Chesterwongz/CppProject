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

std::unordered_set<int> CfgStorage::getNextStmtsFrom(
    const std::string& procName, int stmtNum) {
  return getStmtsFrom(&CFG::getNextStmtsFrom, procName, stmtNum);
}

std::unordered_set<int> CfgStorage::getPrevStmtsFrom(
    const std::string& procName, int stmtNum) {
  return getStmtsFrom(&CFG::getPrevStmtsFrom, procName, stmtNum);
}

bool CfgStorage::isNext(const std::string& proc, int firstStmtNum,
                        int secondStmtNum) {
  if (procToCfgMap.find(proc) == procToCfgMap.end()) {
    return false;
  }
  return procToCfgMap[proc]->isNext(firstStmtNum, secondStmtNum);
}
