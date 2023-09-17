#include "PQLToken.h"

PQLToken::PQLToken(PQLTokenType type) : type(type) {}

PQLToken::PQLToken(PQLTokenType type, TokenValue string) :
	type(type), value(string) {}

PQLToken::getType() {
	return type;
}

PQLToken::getValue() {
	return value;
}
