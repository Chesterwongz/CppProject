#pragma once

#include <string>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"

class IAffectsReader {
 public:
  virtual ~IAffectsReader() = default;
  virtual std::vector<std::pair<std::string, std::string>>
  getAffectsPairs() = 0;

  virtual bool isAffects(int firstStmtNum, int secondStmtNum) = 0;

  virtual std::vector<std::string> getAffects(int firstStmtNum) = 0;
  virtual std::vector<std::string> getAffectedBy(int secondStmtNum) = 0;
};
