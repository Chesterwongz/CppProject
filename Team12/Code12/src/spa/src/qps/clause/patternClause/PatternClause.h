#pragma once

#include <string>
#include <unordered_set>
#include "qps/token/QueryToken.h"
#include "qps/clause/Clause.h"
#include "pkb/facade/PKBReader.h"
#include "qps/argument/IArgument.h"

using std::string, std::unique_ptr, std::vector;

typedef vector<unique_ptr<IArgument>> PatternArgsStream;
typedef unique_ptr<PatternArgsStream> PatternArgsStreamPtr;

class PatternClause : public Clause {
private:
    const string PATTERN_ASSIGN_TYPE = "assign";

    unique_ptr<IArgument> synonym;
    PatternArgsStreamPtr patternArgsStreamPtr;

public:
    // prolly will have to add one more field that specifies if the pattern arg is a direct or partial match
    explicit PatternClause(unique_ptr<IArgument> synonym, PatternArgsStreamPtr patternArgsStreamPtr);

    QueryResult evaluate(
            Context context,
            PKBReader &pkb,
            string &synonymToQuery) override;
};
