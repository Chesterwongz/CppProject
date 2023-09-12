#include "qps/token/suchThatToken/SuchThatToken.h"

SuchThatToken::SuchThatToken(Abstraction relationship, Reference first, Reference second) :
relationship(relationship),
firstArg(first),
secondArg(second) {}

const Abstraction SuchThatToken::getRelationship() {
    return relationship;
}

const Reference SuchThatToken::getFirstArgument() {
    return firstArg;
}

const Reference SuchThatToken::getSecondArgument() {
    return secondArg;
}

unique_ptr<Clause> SuchThatToken::buildClause() {
    // placeholder
    return nullptr;
}

