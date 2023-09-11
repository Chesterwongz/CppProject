#pragma once

#include <string>
#include <map>
//#include "qps/token/declarativeToken/DeclarativeToken.h"

using std::string, std::map;

typedef string Synonym;
typedef string Entity;

class Context {
private:
    map<string, Entity> tokenNameToTokenMap = {};

public:
    void addToken(Synonym tokenSynonym, Entity tokenEntity);

    Entity getTokenEntity(Synonym &tokenName);
};
