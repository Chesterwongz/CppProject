#pragma once

#include "PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ParentsAbstraction : public IAbstraction {
public:
    explicit ParentsAbstraction(AbstractionParams *abstractionParams) :
            IAbstraction(abstractionParams) {};
    std::set<int> getAbstractions() override;
};