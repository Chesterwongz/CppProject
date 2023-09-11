#include "Query.h"

Query::Query(PKBReader *pkb) : pkb(pkb) {}

void Query::addSynonym(DeclarativeToken *token) {
    this->context.addToken(token);
}

void Query::addClause(std::unique_ptr<Clause> &clause) {
    this->clauses.push_back(std::move(clause));
}

std::unordered_set<int> Query::evaluate() {
    for (std::unique_ptr<Clause> &clause : clauses) {
        clause->evaluate(this->context, pkb);
    }
}
