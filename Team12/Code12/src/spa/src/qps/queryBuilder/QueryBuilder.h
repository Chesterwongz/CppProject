#pragma once

#include "PKB.h"
#include "qps/query/Query.h"
#include "qps/token/Token.h"

class QueryBuilder {
private:
    PKB *pkb;

public:
    Query *buildQuery(Token *token, PKB *pkb);
};