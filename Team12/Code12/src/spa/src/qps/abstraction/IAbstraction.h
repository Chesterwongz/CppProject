#pragma once

#include <unordered_set>
#include "pkb/facade/PKB.h"
#include "qps/token/QueryToken.h"
#include "pkb/facade/PKBReader.h"
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/clause/utils/ClauseConstants.h"

using std::shared_ptr;

struct AbstractionParams {
    PKBReader &pkb;
    Context context;
    Abstraction abstraction;
    shared_ptr<IArgument> firstArg;
    shared_ptr<IArgument> secondArg;
};

class IAbstraction {
protected:
    PKBReader &pkb;
    Context context;
    Abstraction abstraction;
    shared_ptr<IArgument> firstArg;    // (@yq i changed from reference to string)
    shared_ptr<IArgument> secondArg;   // (@yq i changed from reference to string)
    explicit IAbstraction(struct AbstractionParams *params) :
            pkb(params->pkb),
            context(params->context),
            abstraction(params->abstraction),
            firstArg(std::move(params->firstArg)),
            secondArg(std::move(params->secondArg)) {};
public:
    virtual QueryResult getAbstractions() = 0;
};
