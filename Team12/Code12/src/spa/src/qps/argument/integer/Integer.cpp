#include <string>

#include "../IArgument.h"
#include "Integer.h"

string Integer::getValue() {
	return integerValue;
}

string Integer::getArgumentType() {
	return argumentType;
}

bool Integer::isIdent() {
	return false;
}

bool Integer::isInteger() {
	return true;
}

bool Integer::isSynonym() {
	return false;
}

bool Integer::isWildcard() {
	return false;
}
