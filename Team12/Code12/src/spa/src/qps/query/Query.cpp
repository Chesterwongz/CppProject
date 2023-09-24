#include "Query.h"
#include "../clause/utils/ClauseConstants.h"
#include "../intermediateTable/IntermediateTableFactory.h"


Query::Query(PKBReader &pkb) : pkb(pkb) {}


void Query::addContext(unique_ptr<Context> context) {
    this->context = std::move(context);
}

void Query::addClause(unique_ptr<Clause> clause) {
    this->clauses.push_back(std::move(clause));
}

void Query::setSynonymToQuery(const string& selectSynonym) {
    this->synonymToQuery = selectSynonym;
}

set<string> Query::evaluate() {
    // for "select *" requests without any clauses
    if (clauses.empty()) {
        return returnAllPossibleQueriedSynonym();
    }

    // iteratively join results of each clause
    IntermediateTable currIntermediateTable = IntermediateTableFactory::buildWildcardIntermediateTable();
    for (unique_ptr<Clause> &clause : clauses) {
        IntermediateTable clauseResult = clause->evaluate(*context, pkb);
        currIntermediateTable = currIntermediateTable.join(clauseResult);
    }

    // if table evaluates to TRUE (i.e., wildcard),
    // same as "select *" requests without any clauses
    if (currIntermediateTable.isTableWildcard()) {
        return returnAllPossibleQueriedSynonym();
    }

    bool isColMissing = !currIntermediateTable.isColExists(this->synonymToQuery);
    bool isTableNonEmpty = currIntermediateTable.getRowCount() != 0;
    if (isColMissing && isTableNonEmpty) {
        return returnAllPossibleQueriedSynonym();
    }

    // get result vector
    vector<string> resultVector = currIntermediateTable.getSingleCol(this->synonymToQuery);
    return {resultVector.begin(), resultVector.end()};

}

// For case where there are no clauses (e.g. Select a).
// Returns all possible results for queried synonym (a).
set<string> Query::returnAllPossibleQueriedSynonym() {
    Entity entity = context->getTokenEntity(this->synonymToQuery);
    if (entity == PROCEDURE_ENTITY) {
        return pkb.getAllProcedures();
    }
    if (entity == VARIABLE_ENTITY) {
        return pkb.getAllVariables();
    }
    if (entity == CONSTANT_ENTITY) {
        return pkb.getAllConstants();
    }
    StmtType stmtType = EntityToStatementType.at(entity);
    return pkb.getStatement(stmtType);
}

bool Query::operator==(const Query &other) {
    bool res = this->context->getMap() == other.context->getMap();

    for (int i = 0; i < this->clauses.size(); i++) {
        res = clauses.at(i)->isEquals(*(other.clauses.at(i)));
        if (!res) return false;
    }

    return res;
}

