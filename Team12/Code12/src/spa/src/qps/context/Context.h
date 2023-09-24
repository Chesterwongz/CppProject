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
    virtual void addSynonym(const Synonym& tokenSynonym, Entity tokenEntity);
    virtual Entity getTokenEntity(const Synonym &tokenName);
    virtual unordered_map<Synonym, Entity>& getMap(); // for testing
};
