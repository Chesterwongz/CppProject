#pragma once

#include <unordered_set>
#include <utility>
#include "pkb/facade/PKB.h"
#include "qps/token/QueryToken.h"
#include "pkb/facade/PKBReader.h"
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::shared_ptr;

struct AbstractionParams {
    PKBReader &pkb;
    Context context;
    Abstraction abstraction;
    IArgument &firstArg;
    IArgument &secondArg;
    bool isTransitive;
    explicit AbstractionParams(PKBReader &pkb,
                               Context context,
                               Abstraction abstraction,
                               IArgument &firstArg,
                               IArgument &secondArg,
                               bool isTransitive) :
                                   pkb(pkb),
                                   context(std::move(context)),
                                   abstraction(std::move(abstraction)),
                                   firstArg(firstArg),
                                   secondArg(secondArg),
                                   isTransitive(isTransitive) {};
};

class IAbstraction {
protected:
    PKBReader pkb;
    Context context;
    Abstraction abstraction;
    IArgument &firstArg;
    IArgument &secondArg;
    bool isTransitive;

    explicit IAbstraction(unique_ptr<AbstractionParams> params);

public:
    virtual IntermediateTable getAbstractions() = 0;
    virtual ~IAbstraction() = default;
};
