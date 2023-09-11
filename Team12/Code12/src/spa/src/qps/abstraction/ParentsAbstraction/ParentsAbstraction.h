#pragma once

#include "PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ParentsAbstraction : public IAbstraction {
public:
    explicit ParentsAbstraction(struct AbstractionParams *abstractionParams) :
            IAbstraction(abstractionParams) {};
    std::unordered_set<int> getAbstractions() override;
};
