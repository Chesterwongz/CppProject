#include "CfgStorage.h"

#include "pkb/utils/FunctionUtils.h"

void CfgStorage::addCfg(const std::string& procName, std::unique_ptr<CFG> cfg) {
  procToCfgMap[procName] = std::move(cfg);
}
