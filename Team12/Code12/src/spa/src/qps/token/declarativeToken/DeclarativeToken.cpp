#include "qps/token/declarativeToken/DeclarativeToken.h"

DeclarativeToken::DeclarativeToken(Entity entity, Synonym synonym) : entity(entity), synonym(synonym) {}

Entity DeclarativeToken::getEntity() {
    return entity;
}

Synonym DeclarativeToken::getSynonym() {
    return synonym;
}

unique_ptr<Clause> DeclarativeToken::buildClause() {
    // by default DeclarativeToken shouldn't be able to build
    return nullptr;
}
