#pragma once

#include "PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ModifiesAbstraction : public IAbstraction {
public:
    ModifiesAbstraction(struct AbstractionParams *abstractionParams)  :
            IAbstraction(abstractionParams) {};
    std::unordered_set<int> getAbstractions() override;
};
