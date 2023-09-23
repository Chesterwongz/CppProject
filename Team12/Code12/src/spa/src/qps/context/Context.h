#pragma once

#include <string>
#include <unordered_map>

using std::string, std::unordered_map;

typedef string Synonym;
typedef string Entity;

class Context {
private:
    unordered_map<Synonym, Entity> tokenNameToTokenMap = {};

public:
    void addSynonym(Synonym tokenSynonym, Entity tokenEntity);
    Entity getTokenEntity(const Synonym &tokenName);
    unordered_map<Synonym, Entity>& getMap(); // for testing
};
