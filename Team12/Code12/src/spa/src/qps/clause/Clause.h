#pragma once

#include <string>
#include <set>
#include <unordered_set>
#include "qps/context/Context.h"
#include "pkb/facade/PKBReader.h"

using std::string, std::set, std::map;

typedef string StmtSynonym;
typedef set<string> PossibleValues;
typedef map<StmtSynonym, PossibleValues > QueryResult;

class Clause {
public:
    virtual QueryResult evaluate(
            Context context,
            PKBReader *pkb,
            string &synonymToQuery) = 0;
};
