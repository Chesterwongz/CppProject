#pragma once

#include "pkb/interfaces/storage/cfg_storage/ICfgStorage.h"

class CfgStorage : public ICfgStorage {
 private:
  std::unordered_map<std::string, std::unique_ptr<CFG>> procToCfgMap;

 public:
  void addCfg(const std::string& procName, std::unique_ptr<CFG> cfg) override;

  std::vector<std::pair<std::string, std::string>> getNextPairs() override;
};
