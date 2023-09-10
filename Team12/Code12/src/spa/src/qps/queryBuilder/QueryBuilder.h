#pragma once

#include "pkb/PKBReader.h"
#include "qps/query/Query.h"
#include "qps/token/QueryToken.h"

class QueryBuilder {
private:
    PKBReader *pkb;

public:
    explicit QueryBuilder(PKBReader *pkb);
    Query buildQuery(std::vector<QueryToken> *queryTokenVector);
};
