#include "SpToken.h"

SpToken::SpToken(SpTokenType type) : type(type), value(0) {}

SpToken::SpToken(SpTokenType type, string value) : type(type), value(value) {}

SpTokenType SpToken::getType() const { return this->type; }

string SpToken::getValue() const { return this->value; }
