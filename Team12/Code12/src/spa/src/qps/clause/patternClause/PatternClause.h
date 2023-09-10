#pragma once

#include <string>

#include "qps/token/QueryToken.h"

class PatternClause : public Clause {
private:
    Synonym synonym;
    Reference entRef;
    std::string expression;

public:
    explicit PatternClause(Synonym synonym,
                           Reference entRef,
                           std::string expression);
    std::vector<int> evaluate(
            Context context,
            PKBReader pkb) override;};