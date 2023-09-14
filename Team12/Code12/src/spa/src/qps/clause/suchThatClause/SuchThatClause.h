#pragma once

#include <string>
#include <set>
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/clause/Clause.h"

using std::shared_ptr;

class SuchThatClause : public Clause {
private:
    Abstraction relationship;
    shared_ptr<IArgument> firstArg;
    shared_ptr<IArgument> secondArg;

public:
    explicit SuchThatClause(
            Abstraction &relationship,
            unique_ptr<IArgument> &firstArg,
            unique_ptr<IArgument> &secondArg);
    QueryResult evaluate(
            Context context,
            PKBReader *pkb,
            string &synonymToQuery) override;
};
