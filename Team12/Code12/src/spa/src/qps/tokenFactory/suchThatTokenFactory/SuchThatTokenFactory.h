#pragma once

#include "qps/tokenFactory/TokenFactory.h"

class SuchThatTokenFactory : public TokenFactory {
protected:
    const bool isValid(UnvalidatedTokens unvalidatedTokens) override;

public:
    explicit SuchThatTokenFactory() : TokenFactory() {}
    TokenStreamPtr createTokens(ValidatedTokens validatedTokens) override;
};
