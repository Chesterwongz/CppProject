#include "Query.h"

Query::Query(PKB *pkb) : pkb(pkb) {}

void Query::addSynonym(DeclarativeToken *token) {
    this->context[token->getSynonym()] = token;
}

void Query::addClause(Clause *clause) {
    this->clauses.push_back(clause);
}

void Query::evaluate() {
    //todo
}