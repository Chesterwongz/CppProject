#include "SuchThatTokenFactory.h"
#include "qps/token/suchThatToken/SuchThatToken.h"

bool SuchThatTokenFactory::isValid(UnvalidatedTokens unvalidatedTokens) {
    return false;
}

void SuchThatTokenFactory::setRelationship(std::string relationship) {
    SuchThatTokenFactory::relationship = relationship;
}

QPSTokenStreamPtr SuchThatTokenFactory::createTokens(UnvalidatedTokens uvalidatedTokens) {
    return nullptr;
}
