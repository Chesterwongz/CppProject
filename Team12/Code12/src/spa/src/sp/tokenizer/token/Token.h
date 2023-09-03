#pragma once

#include <string>

using std::string;

class Token {
private:
    TokenType type;
    std::string value;
public:
    explicit Token(TokenType type);
    Token(TokenType type, string value);
    [[nodiscard]] TokenType getType() const;
    [[nodiscard]] string getValue() const;
};
