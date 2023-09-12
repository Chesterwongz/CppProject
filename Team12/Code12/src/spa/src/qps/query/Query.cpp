#include "Query.h"

Query::Query(PKBReader *pkb) : pkb(pkb) {}

using namespace std;

void Query::addSynonym(DeclarativeToken *token) {
    this->context.addToken(token->getSynonym(), token->getEntity());
}

void Query::addClause(unique_ptr<Clause> &clause) {
    this->clauses.push_back(std::move(clause));
}

unordered_set<int> Query::evaluate() {
    unordered_set<int> intersectionResult;
    for (unique_ptr<Clause> &clause : clauses) {
        unordered_set<int> clauseResult = clause->evaluate(this->context, pkb);
        if (intersectionResult.empty()) {
            intersectionResult = clauseResult;
            continue;
        }

        // Convert unordered_sets to vectors and sort
        std::vector<int> sortedIntersection(intersectionResult.begin(), intersectionResult.end());
        std::sort(sortedIntersection.begin(), sortedIntersection.end());

        std::vector<int> sortedClauseResult(clauseResult.begin(), clauseResult.end());
        std::sort(sortedClauseResult.begin(), sortedClauseResult.end());

        // Find the intersection
        std::vector<int> result;
        set_intersection(sortedIntersection.begin(), sortedIntersection.end(),
                         sortedClauseResult.begin(), sortedClauseResult.end(),
                         std::back_inserter(result));

// If you need the result in an unordered_set
        intersectionResult = std::unordered_set<int>(result.begin(), result.end());

//
//        set_intersection(intersectionResult.begin(), intersectionResult.end(),
//                         clauseResult.begin(), clauseResult.end(),
//                         inserter(intersectionResult, intersectionResult.begin()));
    }
    return intersectionResult;
}
