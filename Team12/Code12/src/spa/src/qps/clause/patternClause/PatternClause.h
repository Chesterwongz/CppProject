#pragma once

#include <string>
#include <set>
#include "qps/token/QueryToken.h"
#include "qps/clause/Clause.h"

class PatternClause : public Clause {
private:
    Synonym synonym;
    Reference entRef;
    std::string expression;

public:
    explicit PatternClause(Synonym synonym,
                           Reference entRef,
                           std::string expression);
    std::set<int> evaluate(
            Context context,
            PKBReader *pkb) override;};