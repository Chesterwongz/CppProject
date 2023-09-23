#pragma once

#include <string>
#include <unordered_set>
#include "qps/clause/Clause.h"

class SelectClause : public Clause {
private:
    Synonym synonym;

public:
    explicit SelectClause(Synonym synonym);
    QueryResult evaluate(
            Context context,
            PKBReader& pkb,
            string &synonymToQuery) override;
};
