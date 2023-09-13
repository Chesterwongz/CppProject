#pragma once

#include <unordered_set>
#include "pkb/facade/PKB.h"
#include "qps/token/QueryToken.h"
#include "pkb/facade/PKBReader.h"
#include "qps/query/Query.h"
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/clause/utils/ClauseConstants.h"

struct AbstractionParams {
    PKBReader *pkb;
    Context context;
    Abstraction abstraction;
    string firstArg;    // (@yq i changed from reference to string)
    string secondArg;   // (@yq i changed from reference to string)
};

class IAbstraction {
protected:
    PKBReader *pkb{};
    Context context;
    Abstraction abstraction;
    string firstArg;    // (@yq i changed from reference to string)
    string secondArg;   // (@yq i changed from reference to string)
    explicit IAbstraction(struct AbstractionParams *params) :
            pkb(params->pkb),
            context(params->context),
            abstraction(params->abstraction),
            firstArg(params->firstArg),
            secondArg(params->secondArg) {};
public:
    virtual std::unordered_set<int> getAbstractions() = 0;
};
