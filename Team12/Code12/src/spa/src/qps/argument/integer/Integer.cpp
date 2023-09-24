#include <string>

#include "Integer.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

Integer::Integer(const string& argumentValue) {
	if (!QPSStringUtils::isInteger(argumentValue)) {
		throw QPSInvalidQueryException("argumentValue is not an integer");
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

bool Integer::operator==(const IArgument& other) const {
    const auto* otherInteger = dynamic_cast<const Integer*>(&other);
    if (!otherInteger) return false;

    return this->integerValue == otherInteger->integerValue;
}
