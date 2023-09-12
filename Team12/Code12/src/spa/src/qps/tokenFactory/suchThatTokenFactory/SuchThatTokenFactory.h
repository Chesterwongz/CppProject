#pragma once

#include <string>

#include "qps/tokenFactory/TokenFactory.h"

using std::string;

class SuchThatTokenFactory : public TokenFactory {
private:
    string relationship;

protected:
    bool isValid(UnvalidatedTokens unvalidatedTokens) override;

public:
    explicit SuchThatTokenFactory() : relationship("") {}
    void setRelationship(string relationship);
    TokenStreamPtr createTokens(UnvalidatedTokens uvalidatedTokens) override;
};
