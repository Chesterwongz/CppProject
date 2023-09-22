#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ParentsAbstraction : public IAbstraction {
public:
    explicit ParentsAbstraction(unique_ptr<AbstractionParams> abstractionParams) :
            IAbstraction(std::move(abstractionParams)) {};
    IntermediateTable getAbstractions() override;
};
