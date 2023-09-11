#include "Context.h"

Entity Context::getTokenEntity(Synonym &tokenName) {
    return this->tokenNameToTokenMap[tokenName];
};

void Context::addToken(Synonym tokenSynonym, Entity tokenEntity) {
    this->tokenNameToTokenMap[tokenSynonym] = tokenEntity;
};
