#include "qps/token/patternToken/PatternToken.h"

PatternToken::PatternToken(Synonym synonym, Reference entRef, std::string expression) :
synonym(synonym),
entRef(entRef),
expression(expression) {}

const Synonym PatternToken::getSynonym() {
    return synonym;
}

const Reference PatternToken::getFirstArgument() {
    return entRef;
}

const std::string PatternToken::getExpression() {
    return expression;
}