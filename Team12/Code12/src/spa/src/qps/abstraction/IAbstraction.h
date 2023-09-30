#pragma once

#include <unordered_set>

#include <utility>
#include "pkb/facade/PKB.h"
#include "pkb/facade/PKBReader.h"
#include "qps/query/Query.h"
#include "qps/clause/utils/ClauseConstants.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::shared_ptr;

struct AbstractionParams {
    PKBReader &pkb;
    Context &context;
    Abstraction abstraction;
    AbstractArgument &firstArg;
    AbstractArgument &secondArg;
    bool isTransitive;
    explicit AbstractionParams(PKBReader &pkb,
                               Context &context,
                               Abstraction abstraction,
                               AbstractArgument &firstArg,
                               AbstractArgument &secondArg,
                               bool isTransitive) :
                                   pkb(pkb),
                                   context(context),
                                   abstraction(std::move(abstraction)),
                                   firstArg(firstArg),
                                   secondArg(secondArg),
                                   isTransitive(isTransitive) {};
};

class IAbstraction {
protected:
    PKBReader& pkb;
    Context context;
    Abstraction abstraction;
    AbstractArgument &firstArg;
    AbstractArgument &secondArg;
    bool isTransitive;

    explicit IAbstraction(AbstractionParams &params);

public:
    virtual IntermediateTable getAbstractions() = 0;
    virtual ~IAbstraction() = default;
};
