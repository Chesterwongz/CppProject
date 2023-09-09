#pragma once

#include "PKB.h"
#include "qps/abstraction/IAbstraction.h"

class ParentsAbstraction : public IAbstraction {
public:
    explicit ParentsAbstraction(AbstractionParams abstractionParams) :
            IAbstraction(abstractionParams) {};
    std::vector<std::string> getAllPossibleFirstRef() override;
    std::vector<std::string> getAllPossibleSecondRef() override;
};