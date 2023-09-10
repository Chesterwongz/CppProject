#pragma once

#include "PKB.h"
#include "qps/token/QueryToken.h"
#include "pkb/PKBReader.h"
#include "qps/query/Query.h"
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/clause/utils/ClauseConstants.h"

struct AbstractionParams {
    PKBReader *pkb;
    Context context;
    Abstraction abstraction;
    Reference first;
    Reference second;
};

class IAbstraction {
protected:
    PKBReader *pkb{};
    Context context;
    Abstraction abstraction;
    Reference first;
    Reference second;
    explicit IAbstraction(AbstractionParams *params) :
        pkb(params->pkb),
        context(params->context),
        abstraction(params->abstraction),
        first(params->first),
        second(params->second) {};
public:
    virtual std::set<int> getAbstractions() = 0;
};
