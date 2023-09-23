#include "qps/query/Query.h"
#include "pkb/facade/PKB.h"
#include "QueryBuilder.h"

QueryBuilder::QueryBuilder(PKBReader &pkb) : pkb(pkb) {}

Query QueryBuilder::buildQuery(QPSTokenStream& queryTokenVector) {
    auto newQuery = Query(pkb);
    for (int i = 0; i < queryTokenVector.size(); i++) {
        // TODO: refactor chained if-else after integration
        auto queryToken = std::move(queryTokenVector.at(i));
        if (auto *declarativeToken = dynamic_cast<DeclarativeToken*>(queryToken.get())) {
            newQuery.addSynonym(std::move(declarativeToken));
        } else if (auto *selectToken = dynamic_cast<SelectToken*>(queryToken.get())) {
            newQuery.setSynonymToQuery(std::move(selectToken));
        } else {
            std::unique_ptr<Clause> clause = std::move(queryToken->buildClause());
            newQuery.addClause(clause);
        }
    }
    return newQuery;
}
