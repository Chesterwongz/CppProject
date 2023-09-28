#pragma once

#include <string>
#include <set>
#include "qps/clause/Clause.h"
#include "qps/clause/utils/ClauseConstants.h"
#include "qps/argument/IArgument.h"
#include "qps/abstractionEvaluator/AbstractionEvaluator.h"

using std::unique_ptr;

class SuchThatClause : public Clause {
private:
    Abstraction relationship;
    unique_ptr<IArgument> firstArg;
    unique_ptr<IArgument> secondArg;
    bool isTransitive;

public:
    explicit SuchThatClause(
            Abstraction relationship,
            unique_ptr<IArgument> firstArg,
            unique_ptr<IArgument> secondArg,
            bool isTransitive);
    IntermediateTable evaluate(
            Context& context,
            PKBReader& pkb) override;
    bool isEquals(const Clause& other) override;
};
