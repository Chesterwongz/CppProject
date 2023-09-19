#pragma once

#include <string>
#include <set>
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/clause/Clause.h"
#include "qps/argument/IArgument.h"

using std::unique_ptr;

class SuchThatClause : public Clause {
private:
    Abstraction relationship;
    unique_ptr<IArgument> firstArg;
    unique_ptr<IArgument> secondArg;
    bool isTransitive;

public:
    explicit SuchThatClause(
            Abstraction &relationship,
            unique_ptr<IArgument> &firstArg,
            unique_ptr<IArgument> &secondArg,
            bool isTransitive);
    IntermediateTable evaluate(
            Context context,
            PKBReader *pkb,
            string &synonymToQuery) override;
};
