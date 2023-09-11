#include "Query.h"

Query::Query(PKBReader *pkb) : pkb(pkb) {}

using namespace std;

void Query::addSynonym(DeclarativeToken *token) {
    this->context.addToken(token);
}

void Query::addClause(unique_ptr<Clause> &clause) {
    this->clauses.push_back(std::move(clause));
}

unordered_set<int> Query::evaluate() {
    unordered_set<int> intersectionResult;
    for (unique_ptr<Clause> &clause : clauses) {
        unordered_set<int> clauseResult = clause->evaluate(this->context, pkb);
        set_intersection(intersectionResult.begin(), intersectionResult.end(),
                         clauseResult.begin(), clauseResult.end(),
                         inserter(intersectionResult, intersectionResult.begin()));
    }
    return intersectionResult;
}
