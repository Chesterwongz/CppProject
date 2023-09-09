#pragma once

#include "qps.h"
#include "qps/exceptions/QpsException.h"

QPS::QPS(PKBReader *pkb) :
    pkb(pkb),
    tokeniser(new Tokeniser()),
    validator(new Validator()),
    queryBuilder(new QueryBuilder(pkb)) {}

QPS::~QPS() {
    delete (tokeniser);
    delete (validator);
    delete (queryBuilder);
}

void QPS::processQueryString(std::string &queryString) {
    std::vector<QueryToken> *queryTokenVector = tokeniser->convertToTokens(queryString);

    bool isTokensValid = validator->validateTokens(queryTokenVector);
    if (!isTokensValid) {
        throw QpsException::InvalidQueryException();
    }

    // build query from validated tokens
    Query *query = queryBuilder->buildQuery(queryTokenVector);

    query->evaluate();
}
