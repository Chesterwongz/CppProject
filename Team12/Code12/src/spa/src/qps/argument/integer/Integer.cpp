#include <string>

#include "Integer.h"

Integer::Integer(const string& argumentValue) {
	if (!QPSStringUtils::isInteger(argumentValue)) {
		throw std::runtime_error("argumentValue is not an integer");
	}

	integerValue = argumentValue;
}

string Integer::getValue() {
	return integerValue;
}

QPSStringUtils::ArgumentType Integer::getArgumentType() {
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
