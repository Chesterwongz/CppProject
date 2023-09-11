#pragma once

#include <string>

#include "qps/token/QueryToken.h"

class SelectToken : public QueryToken {
private:
    Synonym synonym;

public:
    explicit SelectToken(Synonym synonym);
    std::string getSynonym();
};
