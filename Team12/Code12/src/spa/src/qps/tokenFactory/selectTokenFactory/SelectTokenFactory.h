#pragma once

#include <string>
#include "qps/tokenFactory/TokenFactory.h"

class SelectTokenFactory : public TokenFactory {
protected:
    bool isValid(UnvalidatedTokens unvalidatedTokens) override;

public:
    explicit SelectTokenFactory() : TokenFactory() {}
    TokenStreamPtr createTokens(UnvalidatedTokens unvalidatedTokens) override;
};
