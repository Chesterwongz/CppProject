#pragma once

#include <string>
#include <memory>

#include "qps/token/QueryToken.h"

using std::unique_ptr, std::make_unique;

class SelectToken : public QueryToken {
private:
    SynonymType synonym;

public:
    explicit SelectToken(SynonymType synonym);
    std::string getSynonym();
    unique_ptr<Clause> buildClause() override;
};
