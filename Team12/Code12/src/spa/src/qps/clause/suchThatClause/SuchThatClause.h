#pragma once

#include <string>
#include <set>
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/clause/Clause.h"

class SuchThatClause : public Clause {
private:
    Abstraction relationship;
    IArgument* firstArg;
    IArgument* secondArg;

public:
    explicit SuchThatClause(
            Abstraction &relationship,
            IArgument* firstArg,
            IArgument* secondArg);
    std::unordered_set<int> evaluate(
            Context context,
            PKBReader *pkb) override;
};
