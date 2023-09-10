#include "Query.h"

Query::Query(PKBReader *pkb) : pkb(pkb) {}

void Query::addSynonym(DeclarativeToken *token) {
    this->context.addToken(token);
}

void Query::addClause(unique_ptr<Clause> &clause) {
    this->clauses.push_back(std::move(clause));
}

void Query::evaluate() {
    for (Clause *clause : clauses) {
        clause->evaluate(this->context, pkb);
    }
}
