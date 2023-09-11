#include "qps/token/declarativeToken/DeclarativeToken.h"

DeclarativeToken::DeclarativeToken(Entity entity, Synonym synonym) : entity(entity), synonym(synonym) {}

Entity DeclarativeToken::getEntity() {
    return entity;
}

Synonym DeclarativeToken::getSynonym() {
    return synonym;
}

//Clause QueryToken::buildClause() {
//    return new Clause
//}
