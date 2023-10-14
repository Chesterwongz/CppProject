#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"

class UsesAbstraction : public BaseAbstraction {
 private:
  IntermediateTable handleSynonymOrWildcardArgs();

 public:
  explicit UsesAbstraction(AbstractionParams abstractionParams)
      : BaseAbstraction(abstractionParams) {}

  IntermediateTable evaluateSynonymSynonym() override;
  IntermediateTable evaluateSynonymIdent() override;
  IntermediateTable evaluateSynonymWildcard() override;

  IntermediateTable evaluateIntegerSynonym() override;
  IntermediateTable evaluateIntegerIdent() override;
  IntermediateTable evaluateIntegerWildcard() override;
};
