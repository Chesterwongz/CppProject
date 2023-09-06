#include "Token.h"

Token::Token(TokenType type) : type(type), value(0) {}

Token::Token(TokenType type, string value) : type(type), value(value){}

TokenType Token::getType() const {
    return this->type;
}

string Token::getValue() const {
    return this->value;
}
