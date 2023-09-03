#pragma once

#include <string>
#include "qps/token/Token.h"

class DeclarativeToken : public Token {
public:
    std::string getSynonym();
};