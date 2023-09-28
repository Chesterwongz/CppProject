#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class UsesAbstraction : public IAbstraction {
private:
    IntermediateTable handleSynonymOrWildcardArgs();
public:
    explicit UsesAbstraction(AbstractionParams abstractionParams) :
        IAbstraction(abstractionParams) {};

    IntermediateTable evaluateSynonymSynonym() override;
    IntermediateTable evaluateSynonymIdent() override;
    IntermediateTable evaluateSynonymWildcard() override;

    IntermediateTable evaluateIntegerSynonym() override;
    IntermediateTable evaluateIntegerIdent() override;
    IntermediateTable evaluateIntegerWildcard() override;

    IntermediateTable evaluateWildcardSynonym() override;
    IntermediateTable evaluateWildcardIdent() override;
    IntermediateTable evaluateWildcardWildcard() override;
};
