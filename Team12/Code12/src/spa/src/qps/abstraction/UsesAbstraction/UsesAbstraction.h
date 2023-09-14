#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class UsesAbstraction : public IAbstraction {
public:
    UsesAbstraction(AbstractionParams *abstractionParams) :
        IAbstraction(abstractionParams) {};
    QueryResult getAbstractions() override;
};
