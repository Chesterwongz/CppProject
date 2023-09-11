#pragma once

#include <string>

#include "PKB.h"
#include "qps/tokeniser/Tokeniser.h"
#include "qps/validator/Validator.h"
#include "qps/queryBuilder/QueryBuilder.h"

using std::string;

class QPS {
private:
    PKB *pkb;
    Tokeniser tokeniser;
    Validator validator;
    QueryBuilder queryBuilder;

public:
    explicit QPS(PKB *pkb);
    void processQueryString(string queryString);
};
