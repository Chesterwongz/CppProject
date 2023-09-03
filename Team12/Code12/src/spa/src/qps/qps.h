#pragma once

#include "PKB.h"
#include "qps/tokeniser/tokeniser.h"
#include "qps/validator/validator.h"
#include "qps/queryBuilder/QueryBuilder.h"

class QPS {
private:
    PKB *pkb;
    Tokeniser *tokeniser;
    Validator *validator;
    QueryBuilder *queryBuilder;


public:
    explicit QPS(PKB *pkb);
    ~QPS();
    void processQueryString(std::string &queryString);
};