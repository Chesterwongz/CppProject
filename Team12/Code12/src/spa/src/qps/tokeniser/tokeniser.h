#pragma once

#include <string>
#include "qps/token/token.h"

class Tokeniser {
public:
    Token convertToTokens(std::string &inputString);
};
