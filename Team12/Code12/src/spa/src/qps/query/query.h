#pragma once

#include <vector>
#include "qps/token/token.h"
#include "qps/validator/validator.h"

class Query {
private:
    std::map<std::string, Token*> context;
    std::vector<Clause> clauses;

public:
    void evaluate();
};