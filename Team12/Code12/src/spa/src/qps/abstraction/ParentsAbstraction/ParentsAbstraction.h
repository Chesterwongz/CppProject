#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ParentsAbstraction : public IAbstraction {
public:
    ParentsAbstraction(struct AbstractionParams *abstractionParams) :
            IAbstraction(abstractionParams) {};
    QueryResult getAbstractions() override;
};
