#include <string>

#include "../IArgument.h"
#include "Wildcard.h"

string Wildcard::getValue() {
	return wildcardValue;
}

string Wildcard::getArgumentType() {
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
