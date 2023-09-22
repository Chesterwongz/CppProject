#pragma once

#include <string>
#include <memory>

#include "qps/token/QueryToken.h"
#include "../../argument/IArgument.h"
#include "../../clause/patternClause/PatternClause.h"

using std::string, std::vector, std::unique_ptr;

class PatternToken : public QueryToken {
private:
    unique_ptr<IArgument> synonym;
    PatternArgsStreamPtr patternArgsStreamPtr;
public:
    explicit PatternToken(string synonym, vector<string> unvalidatedTokens);
    SynonymType getSynonym();
    /*Reference getFirstArgument();
    std::string getExpression();*/
    PatternArgsStreamPtr getPatternArgsStreamPtr();
    unique_ptr<Clause> buildClause();
};
