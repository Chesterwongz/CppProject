#include "Context.h"

void Context::addToken(DeclarativeToken *token) {
    Synonym tokenSynonym = token->getSynonym();
    this->tokenNameToTokenMap[tokenSynonym] = token;
};

DeclarativeToken *Context::getToken(Synonym &tokenName) {
    DeclarativeToken *token = this->tokenNameToTokenMap[tokenName];
    return token;
};

Entity Context::getTokenEntity(Synonym &tokenName) {
    DeclarativeToken *token = this->tokenNameToTokenMap[tokenName];
    return token->getEntity();
};
