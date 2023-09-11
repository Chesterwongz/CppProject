#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "qps/token/QueryToken.h"
#include "qps/validator/Validator.h"
#include "pkb/PKBReader.h"
#include "qps/token/declarativeToken/DeclarativeToken.h"
//#include "qps/context/Context.h"
//#include "qps/clause/Clause.h"

typedef std::vector<std::unique_ptr<Clause>> ClauseList;

class Query {
private:
    PKBReader *pkb;
    Context context = Context();
    ClauseList clauses = {};

public:
    explicit Query(PKBReader *pkb);
    void addSynonym(DeclarativeToken *token);
    void addClause(std::unique_ptr<Clause> &clause);
    std::unordered_set<int> evaluate();
};
