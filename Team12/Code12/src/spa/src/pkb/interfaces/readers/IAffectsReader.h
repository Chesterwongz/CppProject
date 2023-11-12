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

  virtual std::vector<std::string> getAffects(StmtType type2, int s1) = 0;
  virtual std::vector<std::string> getAffectedBy(StmtType type1, int s2) = 0;
};
