#include "CfgStorage.h"

void CfgStorage::addCfg(const std::string& procName, std::unique_ptr<CFG> cfg) {
  procToCfgMap[procName] = std::move(cfg);
}
