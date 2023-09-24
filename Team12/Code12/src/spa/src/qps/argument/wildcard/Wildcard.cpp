#include "Wildcard.h"

string Wildcard::getValue() {
	return wildcardValue;
}

QPSStringUtils::ArgumentType Wildcard::getArgumentType() {
	return argumentType;
}

bool Wildcard::isIdent() {
	return false;
}

bool Wildcard::isInteger() {
	return false;
}

bool Wildcard::isSynonym() {
	return false;
}

bool Wildcard::isWildcard() {
	return true;
}

bool Wildcard::operator==(const IArgument& other) const {
    const auto* otherWildcard = dynamic_cast<const Wildcard*>(&other);
    return otherWildcard;
}
