#pragma once

#include <string>
#include <map>

using std::string, std::map;

typedef string SynonymType;
typedef string Entity;

class Context {
private:
    map<string, Entity> tokenNameToTokenMap = {};

public:
    void addToken(SynonymType tokenSynonym, Entity tokenEntity);

    Entity getTokenEntity(SynonymType&tokenName);
};
