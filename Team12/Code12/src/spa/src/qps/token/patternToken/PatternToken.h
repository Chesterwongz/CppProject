#pragma once

#include <string>

#include "qps/token/QueryToken.h"

class PatternToken : public QueryToken {
private:
    Synonym synonym;
    Reference entRef;
    std::string expression;

public:
    explicit PatternToken(Synonym synonym, Reference entRef, std::string expression);
    const Synonym getSynonym();
    const Reference getFirstArgument();
    const std::string getExpression();
};