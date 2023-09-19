#include <string>

#include "../IArgument.h"
#include "Synonym.h"

string Synonym::getValue() {
	return synonymValue;
}

string Synonym::getArgumentType() {
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
