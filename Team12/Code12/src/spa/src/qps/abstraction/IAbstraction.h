#pragma once

#include "PKB.h"
#include "qps/token/QueryToken.h"
#include "pkb/PKBReader.h"
#include "qps/query/Query.h"
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/clause/utils/ClauseConstants.h"
#include "qps/abstraction/AbstractionFactory.h"

struct AbstractionParams {
    PKBReader *pkb;
    Context context;
    Abstraction abstraction;
    Reference firstArg;
    Reference secondArg;
};

class IAbstraction {
protected:
    PKBReader *pkb{};
    Context context;
    Abstraction abstraction;
    Reference firstArg;
    Reference secondArg;
    explicit IAbstraction(struct AbstractionParams *params) :
            pkb(params->pkb),
            context(params->context),
            abstraction(params->abstraction),
            firstArg(params->firstArg),
            secondArg(params->secondArg) {};
public:
    virtual std::set<int> getAbstractions() = 0;
};
