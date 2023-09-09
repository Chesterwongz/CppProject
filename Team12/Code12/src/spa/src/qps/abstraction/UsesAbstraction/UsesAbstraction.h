#pragma once

#include "PKB.h"
#include "qps/abstraction/IAbstraction.h"

class UsesAbstraction : public IAbstraction {
public:
    explicit UsesAbstraction(AbstractionParams abstractionParams) :
        IAbstraction(abstractionParams) {};
    std::vector<std::string> getAllPossibleFirstRef() override;
    std::vector<std::string> getAllPossibleSecondRef() override;
};