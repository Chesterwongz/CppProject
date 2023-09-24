#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>

#include "pkb/facade/PKBReader.h"
#include "qps/clause/Clause.h"

using std::set, std::vector, std::unique_ptr, std::string;

typedef vector<unique_ptr<Clause>> ClauseList;

class Query {
private:
    PKBReader& pkb;
    unique_ptr<Context> context;
    ClauseList clauses = {};
    // e.g. `Select a such that ...`
    //   -> `a` is the synonymToQuery
    string synonymToQuery;

public:
    explicit Query(PKBReader &pkb);
    void addContext(unique_ptr<Context> context);
    void addClause(unique_ptr<Clause> clause);
    void setSynonymToQuery(const string& selectSynonym);
    set<string> returnAllPossibleQueriedSynonym();
    set<string> evaluate();
    bool operator==(const Query &other);
};