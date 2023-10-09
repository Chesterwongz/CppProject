#include "CfgStorage.h"

void CfgStorage::addCfg(const std::string& procName, std::unique_ptr<CFG> cfg) {
  procToCfgMap[procName] = std::move(cfg);
}

std::vector<std::pair<std::string, std::string>> CfgStorage::getNextPairs() {
  std::vector<std::pair<std::string, std::string>> nextPairs;
  // TODO(PKB): maybe can try optimise this ;-;
  for (const auto& [procName, cfg] : procToCfgMap) {
    for (const auto& [firstStmtNum, secondStmtNums] : cfg->getAdjList()) {
      for (const auto& secondStmtNum : secondStmtNums) {
        nextPairs.emplace_back(std::to_string(firstStmtNum),
                               std::to_string(secondStmtNum));
      }
    }
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
