#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/StmtToStmtAbstraction.h"

class FollowsStarAbstraction : public StmtToStmtAbstraction {
 private:
  IntermediateTable handleSynonymOrWildcardArgs() override;
  IntermediateTable handleBothArgsInteger() override;
  IntermediateTable handleFirstArgInteger() override;
  IntermediateTable handleSecondArgInteger() override;

 public:
  explicit FollowsStarAbstraction(AbstractionParams &abstractionParams)
      : StmtToStmtAbstraction(abstractionParams,
                              &PKBReader::getFollowsStarPairs,
                              &PKBReader::isFollowsStar) {}
};
