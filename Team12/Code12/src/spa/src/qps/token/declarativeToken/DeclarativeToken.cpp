#include "qps/token/declarativeToken/DeclarativeToken.h"

DeclarativeToken::DeclarativeToken(Entity entity, Synonym synonym) : entity(entity), synonym(synonym) {}

const Entity DeclarativeToken::getEntity() {
    return entity;
}

const Synonym DeclarativeToken::getSynonym() {
    return synonym;
}

//Clause QueryToken::buildClause() {
//    return new Clause
//}
