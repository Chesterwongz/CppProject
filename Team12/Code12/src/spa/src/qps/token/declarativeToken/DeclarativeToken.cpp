#include "qps/token/declarativeToken/DeclarativeToken.h"

DeclarativeToken::DeclarativeToken(Entity entity, SynonymType synonym) : entity(entity), synonym(synonym) {}

Entity DeclarativeToken::getEntity() {
    return entity;
}

SynonymType DeclarativeToken::getSynonym() {
    return synonym;
}

unique_ptr<Clause> DeclarativeToken::buildClause() {
    // by default DeclarativeToken shouldn't be able to build
    return nullptr;
}
