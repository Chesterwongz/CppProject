#pragma once

#include <vector>
#include "qps/token/QueryToken.h"
#include "qps/validator/Validator.h"
#include "pkb/PKBReader.h"
#include "qps/token/declarativeToken/DeclarativeToken.h"

class Query {
private:
    PKBReader *pkb;
    std::map<std::string, QueryToken*> context = {};
    std::vector<Clause*> clauses = {};

public:
    explicit Query(PKBReader *pkb);
    void addSynonym(DeclarativeToken *token);
    void addClause(Clause *clause);
    void evaluate();
};