#pragma once


#include <vector>
#include <string>

#include "qps/tokeniser/Tokeniser.h"
#include "qps/token/QueryToken.h"

// Following Factory Method Pattern
// lexical validator + token factory method

typedef std::vector<std::string> ValidatedTokens;

class TokenFactory {
public:
    virtual QueryToken createToken(ValidatedTokens validatedTokens) = 0;
    virtual bool isCorrectSyllabi(UnvalidatedTokens unvalidatedTokens) = 0;
};
