#include <utility>
#include <vector>
#include <memory>
#include <algorithm>

#include "qps/exceptions/QPSException.h"
#include "QPS.h"

using std::string, std::vector, std::unique_ptr;

QPS::QPS(PKBReader *pkb) :
    pkb(pkb),
    tokeniser(Tokeniser()),
    validator(Validator()),
    queryBuilder(QueryBuilder(pkb)) {}

 unordered_set<int> QPS::processQueryString(string queryString) {
    queryString.erase(std::remove(queryString.begin(), queryString.end(), '\n'), queryString.end());
    QPSTokenStream queryTokenVector = tokeniser.convertToTokens(std::move(queryString));

    bool isTokensValid = validator.validateTokens(queryTokenVector);
    if (!isTokensValid) {
        throw QPSException::InvalidQueryException();
    }

    // build query from validated tokens
    Query query = queryBuilder.buildQuery(queryTokenVector);

     return query.evaluate();
}
