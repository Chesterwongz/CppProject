#include <vector>
#include <memory>

#include "qps/exceptions/QpsException.h"
#include "QPS.h"

using std::string, std::vector, std::unique_ptr;

QPS::QPS(PKBReader *pkb) :
    pkb(pkb),
    tokeniser(Tokeniser()),
    validator(Validator()),
    queryBuilder(QueryBuilder(pkb)) {}

void QPS::processQueryString(string queryString) {
    TokenStream queryTokenVector = tokeniser.convertToTokens(queryString);

    bool isTokensValid = validator.validateTokens(queryTokenVector);
    if (!isTokensValid) {
        throw QpsException::InvalidQueryException();
    }

    // build query from validated tokens
    Query query = queryBuilder.buildQuery(queryTokenVector);

    query.evaluate();
}
