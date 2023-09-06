#pragma once

#include <string>
#include "TokenType.h"

using std::string;

class Token {
private:
    TokenType type;
    string value;
public:
    explicit Token(TokenType type);
    Token(TokenType type, string value);
    [[nodiscard]] TokenType getType() const;
    [[nodiscard]] string getValue() const;
};
