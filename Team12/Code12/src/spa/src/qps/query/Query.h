#pragma once

#include <vector>
#include "qps/token/QueryToken.h"
#include "qps/validator/Validator.h"
#include "PKB.h"
#include "qps/token/declarativeToken/DeclarativeToken.h"

class Query {
private:
    PKB *pkb;
    std::map<std::string, QueryToken*> context = {};
    std::vector<unique_ptr<Clause>> clauses = {};

public:
    explicit Query(PKB *pkb);
    void addSynonym(DeclarativeToken *token);
    void addClause(unique_ptr<Clause> &clause);
    void evaluate();
};
