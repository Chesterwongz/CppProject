#include <string>

#include "../IArgument.h"
#include "Wildcard.h"
#include <iostream>

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
