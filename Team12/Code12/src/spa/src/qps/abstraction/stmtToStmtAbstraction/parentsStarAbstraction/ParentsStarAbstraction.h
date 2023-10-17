#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/StmtToStmtAbstraction.h"

class ParentsStarAbstraction : public StmtToStmtAbstraction {
 private:
  IntermediateTable handleFirstArgInteger() override;
  IntermediateTable handleSecondArgInteger() override;

 public:
  explicit ParentsStarAbstraction(AbstractionParams abstractionParams)
      : StmtToStmtAbstraction(abstractionParams,
                              &PKBReader::getParentChildStarPairs,
                              &PKBReader::isParentStar) {}
};
