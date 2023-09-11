#pragma once

#include <string>
#include <memory>

#include "qps/token/QueryToken.h"

using std::unique_ptr;

class PatternToken : public QueryToken {
private:
    Synonym synonym;
    Reference entRef;
    std::string expression;

public:
    explicit PatternToken(Synonym synonym, Reference entRef, std::string expression);
    Synonym getSynonym();
    Reference getFirstArgument();
    std::string getExpression();
    unique_ptr<Clause> buildClause();
};
