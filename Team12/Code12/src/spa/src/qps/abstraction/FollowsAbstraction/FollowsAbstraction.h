#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class FollowsAbstraction : public IAbstraction {
public:
    explicit FollowsAbstraction(struct AbstractionParams *abstractionParams)  :
            IAbstraction(abstractionParams) {};
    IntermediateTable getAbstractions() override;
};
