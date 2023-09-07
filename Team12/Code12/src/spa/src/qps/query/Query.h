#pragma once

#include <vector>
#include "qps/token/QueryToken.h"
#include "qps/validator/Validator.h"
#include "PKB.h"

class Query {
private:
    PKB *pkb;
    std::map<std::string, QueryToken*> context = {};
    std::vector<Clause> clauses = {};

public:
    explicit Query(PKB *pkb);
    void evaluate();
};