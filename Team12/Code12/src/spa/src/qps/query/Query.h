#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "qps/token/QueryToken.h"
#include "qps/validator/Validator.h"
#include "pkb/facade/PKBReader.h"
#include "qps/token/declarativeToken/DeclarativeToken.h"

typedef std::vector<std::unique_ptr<Clause>> ClauseList;

class Query {
private:
    PKBReader& pkb;
    unique_ptr<Context> context;
    ClauseList clauses = {};

public:
    explicit Query(PKBReader& pkb);
    void addContext(unique_ptr<Context> context);
    void addClause(unique_ptr<Clause> clause);
    std::unordered_set<int> evaluate();
};
