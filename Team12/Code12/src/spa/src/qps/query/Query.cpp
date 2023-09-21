#include "Query.h"
#include "../clause/utils/ClauseConstants.h"
#include "../intermediateTable/IntermediateTableFactory.h"

Query::Query(PKBReader *pkb) : pkb(pkb) {}

using namespace std;

void Query::setSynonymToQuery(SelectToken *token) {
    this->synonymToQuery = token->getSynonym();
}

void Query::addSynonym(DeclarativeToken *token) {
    this->context.addToken(token->getSynonym(), token->getEntity());
}

void Query::addClause(unique_ptr<Clause> &clause) {
    this->clauses.push_back(std::move(clause));
}

set<string> Query::evaluate() {
    // for "select *" requests without any clauses
    if (clauses.empty()) {
        returnAllPossibleQueriedSynonym();
    }

    // iteratively join results of each clause
    IntermediateTable currIntermediateTable = IntermediateTableFactory::buildWildcardIntermediateTable();
    for (unique_ptr<Clause> &clause : clauses) {
        IntermediateTable clauseResult = clause->evaluate(this->context, pkb);
        currIntermediateTable = currIntermediateTable.join(clauseResult);
    }

    // if table evaluates to TRUE (i.e., wildcard),
    // same as "select *" requests without any clauses
    if (currIntermediateTable.isTableWildcard()) {
        returnAllPossibleQueriedSynonym();
    }

    // get result vector
    vector<string> resultVector = currIntermediateTable.getSingleCol(this->synonymToQuery);
    return {resultVector.begin(), resultVector.end()};

}

// For case where there are no clauses (e.g. Select a).
// Returns all possible results for queried synonym (a).
set<string> Query::returnAllPossibleQueriedSynonym() {
    Entity entity = context.getTokenEntity(this->synonymToQuery);
    StmtType stmtType = EntityToStatementType.at(entity);
    return pkb->getStatement(stmtType);
}

