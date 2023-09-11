#include "SuchThatTokenFactory.h"
#include "qps/token/suchThatToken/SuchThatToken.h"

const bool SuchThatTokenFactory::isValid(UnvalidatedTokens unvalidatedTokens) {
    return false;
}

void SuchThatTokenFactory::setRelationship(std::string relationship) {
    SuchThatTokenFactory::relationship = relationship;
}

TokenStreamPtr SuchThatTokenFactory::createTokens(UnvalidatedTokens uvalidatedTokens) {
    return nullptr;
}
