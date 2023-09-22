#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ModifiesAbstraction : public IAbstraction {
public:
    explicit ModifiesAbstraction(unique_ptr<AbstractionParams> abstractionParams)  :
            IAbstraction(std::move(abstractionParams)) {};
    IntermediateTable getAbstractions() override;
};
