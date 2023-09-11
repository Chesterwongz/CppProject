#include "qps/query/Query.h"
#include "PKB.h"
#include "QueryBuilder.h"

QueryBuilder::QueryBuilder(PKB *pkb) : pkb(pkb) {}

Query QueryBuilder::buildQuery(TokenStream& queryTokenVector) {
    auto newQuery = Query(pkb);
    for (auto &queryToken : queryTokenVector) {
        if (auto *declarativeToken = dynamic_cast<DeclarativeToken*>(&queryToken)) {
            newQuery.addSynonym(declarativeToken);
        } else {
            std::unique_ptr<Clause> clause = queryToken.buildClause();
            newQuery.addClause(clause);
        }
    }
    return newQuery;
}
