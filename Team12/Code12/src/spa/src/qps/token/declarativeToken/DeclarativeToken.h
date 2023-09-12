#pragma once

#include <string>
#include <memory>
#include "qps/token/QueryToken.h"

using std::unique_ptr;

typedef std::string Entity;

class DeclarativeToken : public QueryToken {
private:
    Entity entity;
    Synonym synonym;

public:
    DeclarativeToken(Entity entity, Synonym synonym);
    Synonym getSynonym();
    Entity getEntity();
    unique_ptr<Clause> buildClause() override;
};
