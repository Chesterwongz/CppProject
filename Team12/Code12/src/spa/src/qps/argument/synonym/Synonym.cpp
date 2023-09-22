#include <string>
#include "Synonym.h"

Synonym::Synonym(string argumentValue) {
	if (!QPSStringUtils::isSynonym(argumentValue)) {
		throw std::runtime_error("argumentValue is not a synonym");
	}

	synonymValue = argumentValue;
}

string Synonym::getValue() {
	return synonymValue;
}

QPSStringUtils::ArgumentType Synonym::getArgumentType() {
	return argumentType;
}

bool Synonym::isIdent() {
	return false;
}

bool Synonym::isInteger() {
	return false;
}

bool Synonym::isSynonym() {
	return true;
}

bool Synonym::isWildcard() {
	return false;
}
