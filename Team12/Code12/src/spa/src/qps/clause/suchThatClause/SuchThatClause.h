#pragma once

#include <string>

#include "qps/token/QueryToken.h"

typedef std::string Abstraction;

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
    std::vector<int> evaluate(
            Context context,
            PKBReader pkb) override;
};