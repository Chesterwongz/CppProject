#pragma once


#include <vector>
#include <string>

#include "qps/tokeniser/Tokeniser.h"
#include "qps/token/QueryToken.h"

// Following Factory Method Pattern
// lexical validator + token factory method

typedef std::vector<std::string> ValidatedTokens;

class TokenFactory {
private:


public:
    explicit TokenFactory(UnvalidatedTokens unvalidatedToken);
    virtual QueryToken createToken(ValidatedTokens validatedTokens);
    virtual bool isCorrectSyllabi(UnvalidatedTokens unvalidatedTokens);
};
