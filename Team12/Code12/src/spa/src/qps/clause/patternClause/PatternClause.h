#pragma once

#include <string>
#include <unordered_set>
#include "qps/token/QueryToken.h"
#include "qps/clause/Clause.h"
#include "pkb/facade/PKBReader.h"

class PatternClause : public Clause {
private:
    Synonym synonym;
    Reference entRef;
    std::string expression;

public:
    explicit PatternClause(Synonym synonym,
                           Reference entRef,
                           std::string expression);
    QueryResult evaluate(
            Context context,
            PKBReader *pkb,
            string &synonymToQuery) override;
};
