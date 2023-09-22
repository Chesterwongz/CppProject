#include "Context.h"

Entity Context::getTokenEntity(SynonymType&tokenName) {
    return this->tokenNameToTokenMap[tokenName];
};

void Context::addToken(SynonymType tokenSynonym, Entity tokenEntity) {
    this->tokenNameToTokenMap[tokenSynonym] = tokenEntity;
};
