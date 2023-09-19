#pragma once

#include <unordered_set>
#include "pkb/facade/PKB.h"
#include "qps/token/QueryToken.h"
#include "pkb/facade/PKBReader.h"
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::shared_ptr;

struct AbstractionParams {
    PKBReader *pkb;
    Context context;
    Abstraction abstraction;
    IArgument &firstArg;
    IArgument &secondArg;
    bool isTransitive;
};

class IAbstraction {
protected:
    PKBReader *pkb{};
    Context context;
    Abstraction abstraction;
    IArgument &firstArg;
    IArgument &secondArg;
    bool isTransitive;

    explicit IAbstraction(struct AbstractionParams *params);

public:
    virtual IntermediateTable getAbstractions() = 0;
};
