#pragma once

#include <map>
#include <string>
#include "qps/token/QueryToken.h"

class Validator {
private:
    std::map<std::string, QueryToken*> declarativeTokensMap;

public:
    bool validateTokens(QueryToken *token);
};
