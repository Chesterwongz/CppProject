#pragma once

#include <string>
#include "qps/token/Token.h"

class Tokeniser {
public:
    Token *convertToTokens(std::string &inputString);
};
