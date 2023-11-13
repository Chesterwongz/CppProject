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

  virtual std::vector<std::string> getAffects(int s1, StmtType type2) = 0;
  virtual std::vector<std::string> getAffectedBy(int s2, StmtType type1) = 0;
  virtual bool hasAffects() = 0;
};
