#pragma once

#include "qps/query/Query.h"
#include "PKB.h"
#include "QueryBuilder.h"

QueryBuilder::QueryBuilder(PKB *pkb) : pkb(pkb) {}

Query *QueryBuilder::buildQuery(Token *token) {
    auto *newQuery = new Query(pkb);
    Token *curr = token;
    while (curr != nullptr) {
        if (auto *declarativeToken = dynamic_cast<DeclarativeToken *>(token)) {
            newQuery->addSynonym(declarativeToken);
        } else {
            Clause *clause = token->build();
            newQuery->addClause(clause);
        }
        curr = token->getNext();
    }
    return (newQuery);
}