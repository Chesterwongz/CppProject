#pragma once

#include <string>
#include <set>
#include "qps/clause/Clause.h"
#include "qps/clause/utils/ClauseConstants.h"
#include "qps/argument/AbstractArgument.h"

using std::unique_ptr;

class SuchThatClause : public Clause {
private:
    Abstraction relationship;
    unique_ptr<AbstractArgument> firstArg;
    unique_ptr<AbstractArgument> secondArg;
    bool isTransitive;

public:
    explicit SuchThatClause(
            Abstraction relationship,
            unique_ptr<AbstractArgument> firstArg,
            unique_ptr<AbstractArgument> secondArg,
            bool isTransitive);
    IntermediateTable evaluate(
            Context& context,
            PKBReader& pkb) override;
    bool isEquals(const Clause& other) override;
};
