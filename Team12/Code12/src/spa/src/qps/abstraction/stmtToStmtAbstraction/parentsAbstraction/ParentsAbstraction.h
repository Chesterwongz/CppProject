#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/StmtToStmtAbstraction.h"

class ParentsAbstraction : public StmtToStmtAbstraction {
 private:
  IntermediateTable handleSynonymOrWildcardArgs() override;
  IntermediateTable handleBothArgsInteger() override;
  IntermediateTable handleFirstArgInteger() override;
  IntermediateTable handleSecondArgInteger() override;

 public:
  explicit ParentsAbstraction(AbstractionParams abstractionParams)
      : StmtToStmtAbstraction(abstractionParams,
                              &PKBReader::getParentChildPairs,
                              &PKBReader::isParent) {}
};
