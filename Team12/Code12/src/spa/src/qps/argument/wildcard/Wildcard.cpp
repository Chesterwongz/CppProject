#include "Wildcard.h"
#include <iostream>

string Wildcard::getValue() {
	return wildcardValue;
}

QPSStringUtils::ArgumentType Wildcard::getArgumentType() {
	return argumentType;
}

bool Wildcard::isWildcard() {
	return true;
}

bool Wildcard::operator==(const IArgument& other) const {
    const auto* otherWildcard = dynamic_cast<const Wildcard*>(&other);
    return otherWildcard;
}
