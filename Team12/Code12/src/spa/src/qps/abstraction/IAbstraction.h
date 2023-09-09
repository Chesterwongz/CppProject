#pragma once

#include "PKB.h"
#include "qps/token/QueryToken.h"
#include "pkb/PKBReader.h"

struct AbstractionParams {
    PKBReader *pkb;
    Reference first;
    Reference second;
};

class IAbstraction {
protected:
    PKBReader *pkb;
    Reference first;
    Reference second;
    explicit IAbstraction(AbstractionParams params) {};
public:
    virtual std::vector<std::string> getAllPossibleFirstRef() = 0;
    virtual std::vector<std::string> getAllPossibleSecondRef() = 0;
};
