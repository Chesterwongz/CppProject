#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"

class ModifiesAbstraction : public BaseAbstraction {
 private:
  IntermediateTable handleSynonymOrWildcardArgs();
  IntermediateTable handleProcNameWithVarSynonymOrWildcard();

 public:
  explicit ModifiesAbstraction(AbstractionParams abstractionParams)
      : BaseAbstraction(abstractionParams) {}

  IntermediateTable evaluateSynonymSynonym() override;
  IntermediateTable evaluateSynonymIdent() override;
  IntermediateTable evaluateSynonymWildcard() override;

  IntermediateTable evaluateIntegerSynonym() override;
  IntermediateTable evaluateIntegerIdent() override;
  IntermediateTable evaluateIntegerWildcard() override;

  IntermediateTable evaluateIdentSynonym() override;
  IntermediateTable evaluateIdentIdent() override;
  IntermediateTable evaluateIdentWildcard() override;
};
