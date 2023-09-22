#pragma once

#include <string>
#include <memory>
#include "qps/token/QueryToken.h"

using std::unique_ptr;

typedef std::string Entity;

class DeclarativeToken : public QueryToken {
private:
    Entity entity;
    SynonymType synonym;

public:
    DeclarativeToken(Entity entity, SynonymType synonym);
    SynonymType getSynonym();
    Entity getEntity();
    unique_ptr<Clause> buildClause() override;
};
