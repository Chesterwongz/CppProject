#pragma once

#include <string>
#include "qps/clause/Clause.h"
#include "qps/token/QueryToken.h"

typedef std::string Entity;

class DeclarativeClause : public Clause {
private:
    Entity entity;
    Synonym synonym;

public:
    DeclarativeClause(Entity entity, Synonym synonym);
};