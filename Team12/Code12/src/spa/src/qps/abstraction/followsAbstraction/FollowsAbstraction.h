#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"

class FollowsAbstraction : public BaseAbstraction {
 private:
  IntermediateTable handleSynonymOrWildcardArgs();
  IntermediateTable handleBothArgsInteger();
  IntermediateTable handleFirstArgInteger();
  IntermediateTable handleSecondArgInteger();

 public:
  explicit FollowsAbstraction(AbstractionParams &abstractionParams)
      : BaseAbstraction(abstractionParams) {}

  IntermediateTable evaluateSynonymSynonym() override;
  IntermediateTable evaluateSynonymInteger() override;
  IntermediateTable evaluateSynonymWildcard() override;

  IntermediateTable evaluateIntegerSynonym() override;
  IntermediateTable evaluateIntegerInteger() override;
  IntermediateTable evaluateIntegerWildcard() override;

  IntermediateTable evaluateWildcardSynonym() override;
  IntermediateTable evaluateWildcardInteger() override;
  IntermediateTable evaluateWildcardWildcard() override;
};
