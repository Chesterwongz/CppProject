#pragma once

#include "qps.h"
#include "qps/exceptions/QpsException.h"

QPS::QPS(PKB *pkb) :
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
    Token *token = tokeniser->convertToTokens(queryString);

    bool isTokensValid = validator->validateTokens(token);
    if (!isTokensValid) {
        throw QpsException::InvalidQueryException();
    }

    // build query from validated tokens
    Query *query = queryBuilder->buildQuery(token);

    query->evaluate();
}
