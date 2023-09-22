#pragma once

#include <string>

#include "qps/tokenFactory/TokenFactory.h"
#include "qps/argument/IArgument.h"

using std::string, std::unique_ptr;

class PatternTokenFactory : public TokenFactory {
private:
    string synonym;

protected:
    bool isValid(UnvalidatedTokens unvalidatedTokens) override;

public:
    explicit PatternTokenFactory() : TokenFactory() {}
    void setSynonym(string synonym);
    QPSTokenStreamPtr createTokens(UnvalidatedTokens unvalidatedTokens) override;
};
