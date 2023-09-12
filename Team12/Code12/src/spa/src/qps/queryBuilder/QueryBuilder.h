#pragma once

#include "pkb/facade/PKBReader.h"
#include "qps/query/Query.h"
#include "qps/token/QueryToken.h"
#include "qps/tokenFactory/TokenFactory.h"

class QueryBuilder {
private:
    PKBReader *pkb;

public:
    explicit QueryBuilder(PKBReader *pkb);
    Query buildQuery(TokenStream& queryTokenVector);
};
