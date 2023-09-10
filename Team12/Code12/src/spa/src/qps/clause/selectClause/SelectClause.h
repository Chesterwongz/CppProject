#pragma once

#include <string>
#include "qps/clause/Clause.h"
#include "qps/token/QueryToken.h"

class SelectClause : public Clause {
private:
    Synonym synonym;

public:
    explicit SelectClause(Synonym synonym);
    std::vector<int> evaluate(Context context) override;
};