#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "qps/token/QueryToken.h"
#include "qps/tokenFactory/TokenFactory.h"

using std::string, std::vector;

class Validator {
private:
    std::unordered_map<string, QueryToken*> declarativeTokensMap;

public:
    bool validateTokens(TokenStream& queryTokenVector);
};
