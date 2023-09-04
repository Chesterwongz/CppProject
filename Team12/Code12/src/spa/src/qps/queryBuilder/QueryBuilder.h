#pragma once

#include "PKB.h"
#include "qps/query/Query.h"
#include "qps/token/QueryToken.h"

class QueryBuilder {
private:
    PKB *pkb;

public:
    Query *buildQuery(QueryToken *token, PKB *pkb);
};