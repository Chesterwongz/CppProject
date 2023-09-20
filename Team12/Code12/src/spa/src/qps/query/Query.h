#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>

#include "qps/token/QueryToken.h"
#include "pkb/facade/PKBReader.h"

using std::unique_ptr;

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
