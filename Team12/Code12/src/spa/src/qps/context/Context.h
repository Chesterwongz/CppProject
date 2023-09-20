#pragma once

#include <string>
#include <map>

using std::string, std::map;

typedef string Synonym;
typedef string Entity;

class Context {
private:
    map<string, Entity> tokenNameToTokenMap = {};

public:
    void addSynonym(Synonym tokenSynonym, Entity tokenEntity);

    Entity getTokenEntity(Synonym &tokenName);
};
