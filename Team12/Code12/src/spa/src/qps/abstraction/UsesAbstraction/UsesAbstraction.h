#pragma once

#include "PKB.h"
#include "qps/abstraction/IAbstraction.h"

class UsesAbstraction : public IAbstraction {
public:
    explicit UsesAbstraction(AbstractionParams *abstractionParams) :
        IAbstraction(abstractionParams) {};
    std::unordered_set<int> getAbstractions() override;
};
