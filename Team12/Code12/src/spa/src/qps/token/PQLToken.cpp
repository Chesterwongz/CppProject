#include "PQLToken.h"

PQLToken::PQLToken(PQLTokenType type) : type(type) {}

PQLToken::PQLToken(PQLTokenType type, const TokenValue &value)
    : type(type), value(value) {}

PQLTokenType PQLToken::getType() { return type; }

TokenValue PQLToken::getValue() { return value; }

void PQLToken::updateTokenType(PQLTokenType tokenType) {
  this->type = tokenType;
}
