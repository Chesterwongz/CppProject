#pragma once

#include <memory>

#include "pkb/facade/PKBReader.h"
#include "qps/query/Query.h"
#include "qps/token/QueryToken.h"
#include "qps/tokenFactory/TokenFactory.h"
#include "qps/context/Context.h"

using std::unique_ptr, std::move;

class QueryBuilder {
private:
    unique_ptr<Query> query;
    PKBReader& pkbReader;
    Context context;
    vector<unique_ptr<Clause>> clauses;

public:
    explicit QueryBuilder(PKBReader& pkb);
    unique_ptr<Query> buildQuery();
    string isExistingSynonym(string synonym); // returns entity type
    void addSynonym(string name, string entity);
};
