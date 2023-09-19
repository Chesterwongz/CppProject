#pragma once

#include "pkb/facade/PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ParentsAbstraction : public IAbstraction {
public:
    explicit ParentsAbstraction(struct AbstractionParams *abstractionParams) :
            IAbstraction(abstractionParams) {};
    IntermediateTable getAbstractions() override;
};
