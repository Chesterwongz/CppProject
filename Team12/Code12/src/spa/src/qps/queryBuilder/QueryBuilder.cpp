#pragma once

#include "qps/query/Query.h"
#include "PKB.h"
#include "QueryBuilder.h"

QueryBuilder::QueryBuilder(PKB *pkb) : pkb(pkb) {}

Query QueryBuilder::buildQuery(std::vector<QueryToken> *queryTokenVector) {
    auto newQuery = Query(pkb);
    for (QueryToken &queryToken : *queryTokenVector) {
        if (auto *declarativeToken = dynamic_cast<DeclarativeToken*>(&queryToken)) {
            newQuery.addSynonym(declarativeToken);
        } else {
            Clause *clause = queryToken.buildClause();
            newQuery.addClause(clause);
        }
    }
    return newQuery;
};
