#include "qps/query/Query.h"
#include "pkb/facade/PKB.h"
#include "QueryBuilder.h"

QueryBuilder::QueryBuilder(unique_ptr<PKBReader>& pkb) : pkb(pkb) {}

Query QueryBuilder::buildQuery(QPSTokenStream& queryTokenVector) {
    auto newQuery = Query(pkb);
    for (int i = 0; i < queryTokenVector.size(); i++) {
        auto queryToken = std::move(queryTokenVector.at(i));
        if (auto *declarativeToken = dynamic_cast<DeclarativeToken*>(queryToken.get())) {
            newQuery.addSynonym(std::move(declarativeToken));
        } else {
            std::unique_ptr<Clause> clause = std::move(queryToken->buildClause());
            newQuery.addClause(clause);
        }
    }
    return newQuery;
}
