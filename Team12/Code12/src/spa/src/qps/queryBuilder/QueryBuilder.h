#pragma once

#include "PKB.h"
#include "qps/query/query.h"
#include "qps/token/token.h"

class QueryBuilder {
private:
    PKB *pkb;

public:
    Query *buildQuery(Token *token);
};