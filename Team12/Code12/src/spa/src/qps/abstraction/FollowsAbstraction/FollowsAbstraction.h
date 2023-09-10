#pragma once

#include "PKB.h"
#include "qps/abstraction/IAbstraction.h"

class FollowsAbstraction : public IAbstraction {
public:
    explicit FollowsAbstraction(struct AbstractionParams *abstractionParams)  :
            IAbstraction(abstractionParams) {};
    std::set<int> getAbstractions() override;
};