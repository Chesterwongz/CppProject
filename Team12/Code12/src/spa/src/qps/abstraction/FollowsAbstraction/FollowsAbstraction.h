#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class FollowsAbstraction : public IAbstraction {
public:
    FollowsAbstraction(struct AbstractionParams *abstractionParams)  :
            IAbstraction(abstractionParams) {};
   QueryResult getAbstractions() override;
};
