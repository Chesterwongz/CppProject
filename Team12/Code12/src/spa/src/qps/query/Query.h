#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "qps/token/QueryToken.h"
#include "qps/validator/Validator.h"
#include "pkb/facade/PKBReader.h"
#include "qps/token/declarativeToken/DeclarativeToken.h"
#include "qps/token/selectToken/SelectToken.h"

using std::set, std::vector, std::unique_ptr, std::string;

typedef vector<unique_ptr<Clause>> ClauseList;

class Query {
private:
    PKBReader& pkb;
    Context context = Context();
    ClauseList clauses = {};
    // e.g. `Select a such that ...`
    //   -> `a` is the synonymToQuery
    string synonymToQuery;

public:
    explicit Query(PKBReader& pkb);
    void setSynonymToQuery(SelectToken *token);
    void addSynonym(DeclarativeToken *token);
    void addClause(std::unique_ptr<Clause> &clause);
    set<string> returnAllPossibleQueriedSynonym();
    set<string> evaluate();
};
