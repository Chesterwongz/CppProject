#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ModifiesAbstraction : public IAbstraction {
public:
    explicit ModifiesAbstraction(AbstractionParams abstractionParams)  :
            IAbstraction(abstractionParams) {};
    IntermediateTable getAbstractions() override;
    IntermediateTable handleIntegerArgs(string stmtNumber);
};
