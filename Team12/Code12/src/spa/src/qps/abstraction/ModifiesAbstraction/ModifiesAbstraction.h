#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ModifiesAbstraction : public IAbstraction {
public:
    ModifiesAbstraction(struct AbstractionParams &abstractionParams)  :
            IAbstraction(abstractionParams) {};
    QueryResult getAbstractions() override;
};
