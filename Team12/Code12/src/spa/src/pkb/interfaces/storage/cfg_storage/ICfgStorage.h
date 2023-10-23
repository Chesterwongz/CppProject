#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/cfg/CFG.h"

class ICfgStorage {
 public:
  virtual ~ICfgStorage() = default;

  virtual void addCfg(const std::string& procName,
                      std::unique_ptr<CFG> cfg) = 0;
};
