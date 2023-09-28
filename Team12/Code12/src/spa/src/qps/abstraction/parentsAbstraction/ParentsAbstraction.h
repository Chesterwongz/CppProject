#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ParentsAbstraction : public IAbstraction {
private:
    IntermediateTable handleNoArgsInteger();
    IntermediateTable handleBothArgsInteger();
    IntermediateTable handleFirstArgInteger();
    IntermediateTable handleSecondArgInteger();
public:
    explicit ParentsAbstraction(AbstractionParams abstractionParams) :
            IAbstraction(abstractionParams) {};
    IntermediateTable getAbstractions() override;

    IntermediateTable handleIntegerArgs(
            string firstArgValue, StmtType firstStmtType,
            string secondArgValue, StmtType secondStmtType);

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
