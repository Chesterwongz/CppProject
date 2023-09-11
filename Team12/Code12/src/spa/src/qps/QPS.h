#pragma once

#include <string>

#include "pkb/PKBReader.h"
#include "qps/tokeniser/Tokeniser.h"
#include "qps/validator/Validator.h"
#include "qps/queryBuilder/QueryBuilder.h"

using std::string;

class QPS {
private:
    PKBReader *pkb;
    Tokeniser tokeniser;
    Validator validator;
    QueryBuilder queryBuilder;

public:
    explicit QPS(PKBReader *pkb);
    void processQueryString(string queryString);
};
