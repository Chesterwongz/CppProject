#pragma once

#include <string>
#include <map>
#include "qps/token/declarativeToken/DeclarativeToken.h"
#include "qps/token/QueryToken.h"

using std::string, std::map;

class Context {
private:
    map<string, DeclarativeToken*> tokenNameToTokenMap = {};

public:
    void addToken(DeclarativeToken *token);
    DeclarativeToken *getToken(Synonym &tokenName);
    Entity getTokenEntity(Synonym &tokenName);
};
