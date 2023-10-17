#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/stmtOrProcToVarAbstraction/StmtOrProcToVarAbstraction.h"

class ModifiesAbstraction : public StmtOrProcToVarAbstraction {
 public:
  explicit ModifiesAbstraction(AbstractionParams abstractionParams);
};
