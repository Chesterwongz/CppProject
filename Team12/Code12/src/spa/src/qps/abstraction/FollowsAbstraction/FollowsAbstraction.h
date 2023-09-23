#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class FollowsAbstraction : public IAbstraction {
public:
    explicit FollowsAbstraction(AbstractionParams &abstractionParams)  :
            IAbstraction(abstractionParams) {};
    IntermediateTable getAbstractions() override;
};
