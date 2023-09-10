#pragma once

#include <string>
#include <set>
#include "qps/token/QueryToken.h"
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/clause/Clause.h"

class SuchThatClause : public Clause {
private:
    Abstraction relationship;
    Reference firstArg;
    Reference secondArg;

public:
    explicit SuchThatClause(
            Abstraction relationship,
            Reference first,
            Reference second);
    std::set<int> evaluate(
            Context context,
            PKBReader *pkb) override;
};