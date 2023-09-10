#pragma once

#include <vector>
#include "qps/token/QueryToken.h"
#include "qps/validator/Validator.h"
#include "pkb/PKBReader.h"
#include "qps/context/Context.h"
#include "qps/clause/Clause.h"

typedef std::vector<unique_ptr<Clause>> ClauseList;

class Query {
private:
    PKBReader *pkb;
    Context context = Context();
    ClauseList clauses = {};

public:
    explicit Query(PKBReader *pkb);
    void addSynonym(DeclarativeToken *token);
    void addClause(unique_ptr<Clause> &clause);
    void evaluate();
};
