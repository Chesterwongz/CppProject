#pragma once

#include "PKB.h"
#include "qps/token/QueryToken.h"
#include "pkb/PKBReader.h"
#include "qps/query/Query.h"

struct AbstractionParams {
    PKBReader *pkb;
    Context context;
    Reference first;
    Reference second;
};

class IAbstraction {
protected:
    PKBReader *pkb{};
    Context context;
    Reference first;
    Reference second;
    explicit IAbstraction(AbstractionParams params) :
        pkb(params.pkb),
        context(params.context),
        first(params.first),
        second(params.second) {};
public:
    virtual std::vector<std::string> getAllPossibleFirstRef() = 0;
    virtual std::vector<std::string> getAllPossibleSecondRef() = 0;
};
