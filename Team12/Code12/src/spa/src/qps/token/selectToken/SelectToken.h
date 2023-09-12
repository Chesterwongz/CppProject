#pragma once

#include <string>
#include <memory>

#include "qps/token/QueryToken.h"

using std::unique_ptr, std::make_unique;

class SelectToken : public QueryToken {
private:
    Synonym synonym;

public:
    explicit SelectToken(Synonym synonym);
    std::string getSynonym();
    unique_ptr<Clause> buildClause() override;
};
