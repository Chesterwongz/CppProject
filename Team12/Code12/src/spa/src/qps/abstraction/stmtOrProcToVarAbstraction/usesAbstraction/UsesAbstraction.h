#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/stmtOrProcToVarAbstraction/StmtOrProcToVarAbstraction.h"

class UsesAbstraction : public StmtOrProcToVarAbstraction {
 public:
  explicit UsesAbstraction(AbstractionParams abstractionParams);
};
