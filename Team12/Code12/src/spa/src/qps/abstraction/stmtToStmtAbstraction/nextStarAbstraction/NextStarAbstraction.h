#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/StmtToStmtAbstraction.h"

class NextStarAbstraction : public StmtToStmtAbstraction {
 private:
  IntermediateTable handleFirstArgInteger() override;
  IntermediateTable handleSecondArgInteger() override;

  IntermediateTable evaluateSynonymSynonym() override;
  IntermediateTable evaluateIntegerInteger() override;

 public:
  explicit NextStarAbstraction(AbstractionParams &abstractionParams)
      : StmtToStmtAbstraction(abstractionParams,
                              &PKBReader::getNextTPairs,
                              &PKBReader::isNextT) {}
};
