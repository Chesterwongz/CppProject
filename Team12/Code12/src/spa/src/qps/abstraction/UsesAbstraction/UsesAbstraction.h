#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class UsesAbstraction : public IAbstraction {
public:
    explicit UsesAbstraction(unique_ptr<AbstractionParams> abstractionParams) :
        IAbstraction(std::move(abstractionParams)) {};
    IntermediateTable getAbstractions() override;
};
