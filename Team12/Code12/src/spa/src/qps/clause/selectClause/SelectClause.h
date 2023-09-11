#pragma once

#include <string>
#include <set>
#include "qps/clause/Clause.h"
#include "qps/token/QueryToken.h"

class SelectClause : public Clause {
private:
    Synonym synonym;

public:
    explicit SelectClause(Synonym synonym);
    std::unordered_set<int> evaluate(
            Context context,
            PKBReader *pkb) override;
};
