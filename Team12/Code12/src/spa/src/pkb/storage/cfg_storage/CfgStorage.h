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

 public:
  void addCfg(const std::string& procName, std::unique_ptr<CFG> cfg) override;
};
