#pragma once

#include <memory>
#include <string>

#include "common/cfg/CFG.h"

class ICfgStorage {
 public:
  virtual ~ICfgStorage() = default;

  virtual void addCfg(const std::string &procName,
                      std::unique_ptr<CFG> cfg) = 0;

  virtual std::vector<std::pair<std::string, std::string>> getNextPairs() = 0;
};
