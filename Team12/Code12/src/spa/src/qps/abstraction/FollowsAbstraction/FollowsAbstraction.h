#pragma once

#include "PKB.h"
#include "qps/abstraction/IAbstraction.h"

class FollowsAbstraction : IAbstraction {
public:
    explicit FollowsAbstraction(AbstractionParams abstractionParams)  :
            IAbstraction(abstractionParams) {};
    std::vector<std::string> getAllPossibleFirstRef() override;
    std::vector<std::string> getAllPossibleSecondRef() override;
};