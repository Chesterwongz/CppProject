#pragma once

#include <string>
#include "qps/token/token.h"

class DeclarativeToken : public Token {
public:
    std::string getSynonym();
};