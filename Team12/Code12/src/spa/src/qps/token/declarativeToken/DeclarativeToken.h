#pragma once

#include <string>
#include "qps/token/QueryToken.h"

typedef std::string Entity;

class DeclarativeToken : public QueryToken {
private:
    Entity entity;
    Synonym synonym;

public:
    DeclarativeToken(Entity entity, Synonym synonym);
    Synonym getSynonym();
    Entity getEntity();
};
