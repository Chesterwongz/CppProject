#pragma once

#include "PKB.h"
#include "qps/abstraction/IAbstraction.h"

class UsesAbstraction : public IAbstraction {
public:
    explicit UsesAbstraction(AbstractionParams *abstractionParams) :
        IAbstraction(abstractionParams) {};
    std::set<int> getAbstractions() override;
};
