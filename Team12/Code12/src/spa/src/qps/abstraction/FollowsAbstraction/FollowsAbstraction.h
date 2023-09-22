#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class FollowsAbstraction : public IAbstraction {
public:
    explicit FollowsAbstraction(unique_ptr<AbstractionParams> abstractionParams)  :
            IAbstraction(std::move(abstractionParams)) {};
    IntermediateTable getAbstractions() override;
};
