#include "CfgStorage.h"

#include "pkb/utils/FunctionUtils.h"

void CfgStorage::addCfg(const std::string& procName, std::unique_ptr<CFG> cfg) {
  procToCfgMap[procName] = std::move(cfg);
}

//void CfgStorage::addNextPairForCfg(
//    const std::unique_ptr<CFG>& cfg,
//    std::vector<std::pair<int, int>>& nextPairs) {
//  for (const auto& [firstStmtNum, secondStmtNums] : cfg->getAdjList()) {
//    for (const auto& secondStmtNum : secondStmtNums) {
//      if (secondStmtNum == common::INVALID_STMT_NUM) {
//        continue;
//      }
//      nextPairs.emplace_back(firstStmtNum, secondStmtNum);
//    }
//  }
//}
//
//std::vector<std::pair<int, int>> CfgStorage::getNextPairs() {
//  std::vector<std::pair<int, int>> nextPairs;
//  for (const auto& [procName, cfg] : procToCfgMap) {
//    addNextPairForCfg(cfg, nextPairs);
//  }
//  return nextPairs;
//}
//
//IntSet CfgStorage::getStmtsFrom(const IntToIntSetMap& (CFG::*cfgFunction)()
//                                    const,
//                                const std::string& procName, int stmtNum) {
//  if (procToCfgMap.find(procName) == procToCfgMap.end()) {
//    return {};
//  }
//  const CFG& procCfg = *procToCfgMap.at(procName);
//  const IntToIntSetMap& stmtToStmtSetMap = (procCfg.*cfgFunction)();
//  if (stmtToStmtSetMap.find(stmtNum) == stmtToStmtSetMap.end()) {
//    return {};
//  }
//  return stmtToStmtSetMap.at(stmtNum);
//}
//
//IntSet CfgStorage::getNextStmts(const std::string& procName, int stmtNum) {
//  return getStmtsFrom(&CFG::getAdjList, procName, stmtNum);
//}
//
//IntSet CfgStorage::getPrevStmts(const std::string& procName, int stmtNum) {
//  return getStmtsFrom(&CFG::getReversedAdjList, procName, stmtNum);
//}
//
//bool CfgStorage::isNext(const std::string& proc, int firstStmtNum,
//                        int secondStmtNum) {
//  if (procToCfgMap.find(proc) == procToCfgMap.end()) {
//    return false;
//  }
//  const IntToIntSetMap& adjList = procToCfgMap.at(proc)->getAdjList();
//  if (adjList.find(firstStmtNum) == adjList.end()) {
//    return false;
//  }
//  IntSet nextStmtsOfFirst = adjList.at(firstStmtNum);
//  return nextStmtsOfFirst.find(secondStmtNum) != nextStmtsOfFirst.end();
//}
//
//IntSet CfgStorage::getTStmtsFrom(const IntToIntSetMap& (CFG::*cfgFunction)()
//                                     const,
//                                 const std::string& procName, int stmtNum) {
//  if (procToCfgMap.find(procName) == procToCfgMap.end()) {
//    return {};
//  }
//  const CFG& procCfg = *procToCfgMap.at(procName);
//  const IntToIntSetMap& stmtToStmtSetMap = (procCfg.*cfgFunction)();
//  if (stmtToStmtSetMap.find(stmtNum) != stmtToStmtSetMap.end()) {
//    return {};
//  }
//  return stmtToStmtSetMap.at(stmtNum);
//}
//
//void CfgStorage::addNextTStmts(int from, int to) {
//  nextTCache[from].insert(to);
//  prevTCache[to].insert(from);
//}
//
//IntSet CfgStorage::getNextTStmts(const std::string& procName, int stmtNum) {
//  return {};
//}
//
//IntSet CfgStorage::getPrevTStmts(const std::string& procName, int stmtNum) {
//  return {};
//}
//std::vector<std::pair<int, int>> CfgStorage::getNextTPairs() { return {}; }
//bool CfgStorage::isNextT(const std::string& proc, int firstStmtNum,
//                         int secondStmtNum) {
//  if (procToCfgMap.find(proc) == procToCfgMap.end()) {
//    return false;
//  }
//  return false;
//  //  return procToCfgMap[proc]->isNextT(firstStmtNum, secondStmtNum);
//}
