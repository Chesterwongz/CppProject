#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"

class ParentsAbstraction : public BaseAbstraction {
private:
    IntermediateTable handleSynonymOrWildcardArgs();
    IntermediateTable handleBothArgsInteger();
    IntermediateTable handleFirstArgInteger();
    IntermediateTable handleSecondArgInteger();
public:
    explicit ParentsAbstraction(AbstractionParams abstractionParams) :
            BaseAbstraction(abstractionParams) {};

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
