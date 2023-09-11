#pragma once

#include <unordered_set>
#include "PKB.h"
#include "qps/token/QueryToken.h"
#include "../../../pkb/facade/PKBReader.h"
#include "qps/query/Query.h"
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/clause/utils/ClauseConstants.h"

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
    virtual std::unordered_set<int> getAbstractions() = 0;
};
