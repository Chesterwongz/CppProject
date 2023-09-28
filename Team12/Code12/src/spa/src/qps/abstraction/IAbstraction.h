#pragma once

#include <unordered_set>

#include <utility>
#include "pkb/facade/PKB.h"
#include "pkb/facade/PKBReader.h"
#include "qps/query/Query.h"
#include "qps/clause/utils/ClauseConstants.h"
#include "qps/argument/IArgument.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "AbstractionUtils.h"

class IAbstraction {
protected:
    PKBReader& pkb;
    Context context;
    Abstraction abstraction;
    IArgument &firstArg;
    IArgument &secondArg;
    string firstArgValue;
    string secondArgValue;
    ArgumentPermutation argumentPermutation;
    bool isTransitive;

    explicit IAbstraction(AbstractionParams &params);

    StmtType getFirstArgStmtType();
    StmtType getSecondArgStmtType();

public:
    ArgumentPermutation getAbstractionPermutation();
    virtual ~IAbstraction() = default;


    virtual IntermediateTable evaluateSynonymSynonym();
    virtual IntermediateTable evaluateSynonymInteger();
    virtual IntermediateTable evaluateSynonymIdent();
    virtual IntermediateTable evaluateSynonymWildcard();

    virtual IntermediateTable evaluateIntegerSynonym();
    virtual IntermediateTable evaluateIntegerInteger();
    virtual IntermediateTable evaluateIntegerIdent();
    virtual IntermediateTable evaluateIntegerWildcard();

    virtual IntermediateTable evaluateIdentSynonym();
    virtual IntermediateTable evaluateIdentInteger();
    virtual IntermediateTable evaluateIdentIdent();
    virtual IntermediateTable evaluateIdentWildcard();

    virtual IntermediateTable evaluateWildcardSynonym();
    virtual IntermediateTable evaluateWildcardInteger();
    virtual IntermediateTable evaluateWildcardIdent();
    virtual IntermediateTable evaluateWildcardWildcard();
};
