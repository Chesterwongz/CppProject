#include "qps/token/patternToken/PatternToken.h"
#include "qps/clause/patternClause/PatternClause.h"

PatternToken::PatternToken(Synonym synonym, Reference entRef, std::string expression) :
synonym(synonym),
entRef(entRef),
expression(expression) {}

Synonym PatternToken::getSynonym() {
    return synonym;
}

Reference PatternToken::getFirstArgument() {
    return entRef;
}

std::string PatternToken::getExpression() {
    return expression;
}

unique_ptr<Clause> PatternToken::buildClause() {
    // placeholder
    return nullptr;
}
