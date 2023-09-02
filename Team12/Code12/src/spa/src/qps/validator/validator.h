#pragma once

#include <map>
#include <string>
#include "qps/token/token.h"

class Validator {
private:
    std::map<Synonym, Token*> declarativeTokensMap;

public:
    bool validateTokens(Token *token);
};
