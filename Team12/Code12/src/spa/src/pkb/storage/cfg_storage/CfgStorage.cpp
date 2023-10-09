#include "CfgStorage.h"

void CfgStorage::addCfg(const std::string& procName, std::unique_ptr<CFG> cfg) {
  procToCfgMap[procName] = std::move(cfg);
}

std::vector<std::pair<std::string, std::string>> CfgStorage::getNextPairs() {
  std::vector<std::pair<std::string, std::string>> nextPairs;
  for (const auto& entry : procToCfgMap) {
    const CFG& procCfg = *entry.second;
  }
  return nextPairs;
}
