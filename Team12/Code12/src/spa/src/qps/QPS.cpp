#pragma once

#include "qps/exceptions/QpsException.h"
#include "QPS.h"

QPS::QPS(PKB *pkb) :
    pkb(pkb),
    tokeniser(Tokeniser()),
    validator(Validator()),
    queryBuilder(QueryBuilder(pkb)) {}

void QPS::processQueryString(std::string &queryString) {
    std::vector<QueryToken> *queryTokenVector = tokeniser.convertToTokens(queryString);

    bool isTokensValid = validator.validateTokens(queryTokenVector);
    if (!isTokensValid) {
        throw QpsException::InvalidQueryException();
    }

    // build query from validated tokens
    Query query = queryBuilder.buildQuery(queryTokenVector);

    query.evaluate();
}
