#pragma once

#include "PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ModifiesAbstraction : IAbstraction {
public:
    explicit ModifiesAbstraction(AbstractionParams abstractionParams)  :
            IAbstraction(abstractionParams) {};
    std::vector<std::string> getAllPossibleFirstRef() override;
    std::vector<std::string> getAllPossibleSecondRef() override;
};