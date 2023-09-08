#pragma once

#include <string>
#include "qps/tokenFactory/TokenFactory.h"

class SelectTokenFactory : public TokenFactory {
protected:
    const bool isValid(UnvalidatedTokens unvalidatedTokens) override;

public:
    explicit SelectTokenFactory() : TokenFactory() {}
    TokenStreamPtr createTokens(ValidatedTokens validatedTokens) override;
};
