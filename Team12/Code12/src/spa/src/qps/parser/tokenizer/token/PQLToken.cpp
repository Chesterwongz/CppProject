#include "PQLToken.h"

#include <utility>

PQLToken::PQLToken(PQLTokenType type) : type(type) {}

PQLToken::PQLToken(PQLTokenType type, TokenValue value)
    : type(type), value(std::move(value)) {}

PQLTokenType PQLToken::getType() { return type; }

TokenValue PQLToken::getValue() { return value; }

void PQLToken::updateTokenType(PQLTokenType tokenType) {
  this->type = tokenType;
}
