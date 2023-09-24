#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class UsesAbstraction : public IAbstraction {
public:
    explicit UsesAbstraction(AbstractionParams abstractionParams) :
        IAbstraction(abstractionParams) {};
    IntermediateTable getAbstractions() override;
    IntermediateTable handleIntegerArgs(string stmtNumber);
};
