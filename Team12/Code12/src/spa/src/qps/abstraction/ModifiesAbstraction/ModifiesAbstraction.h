#pragma once

#include "PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ModifiesAbstraction : public IAbstraction {
public:
    explicit ModifiesAbstraction(struct AbstractionParams *abstractionParams)  :
            IAbstraction(abstractionParams) {};
    std::set<int> getAbstractions() override;
};