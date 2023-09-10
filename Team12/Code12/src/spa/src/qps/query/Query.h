#pragma once

#include <vector>
#include "qps/token/QueryToken.h"
#include "qps/validator/Validator.h"
#include "pkb/PKBReader.h"
#include "qps/token/declarativeToken/DeclarativeToken.h"

typedef std::map<std::string, DeclarativeToken*> Context;
typedef std::vector<Clause*> ClauseList;

class Query {
private:
    PKBReader *pkb;
    Context context = {};
    ClauseList clauses = {};

public:
    explicit Query(PKBReader *pkb);
    void addSynonym(DeclarativeToken *token);
    void addClause(Clause *clause);
    void evaluate();
};