#include "PQLToken.h"

PQLToken::PQLToken(PQLTokenType type) : type(type) {}

PQLToken::PQLToken(PQLTokenType type, TokenValue string) :
	type(type), value(string) {}

const PQLTokenType PQLToken::getType() {
	return type;
}

const TokenValue PQLToken::getValue() {
	return value;
}

void PQLToken::updateTokenType(PQLTokenType type)
{
	this->type = type;
}
