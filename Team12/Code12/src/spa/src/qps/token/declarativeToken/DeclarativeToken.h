#pragma once

#include <string>
#include "qps/token/QueryToken.h"

class DeclarativeToken : public QueryToken {
private:
    Entity entity;
    Synonym synonym;

public:
    explicit DeclarativeToken(Entity entity, Synonym synonym);
    const Synonym getSynonym();
    const Entity getEntity();
};