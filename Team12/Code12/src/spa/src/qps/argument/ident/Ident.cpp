#include <string>

#include "../IArgument.h"
#include "Ident.h"

Ident::Ident(string argumentValue) {
	// remove '\"' from value
	argumentValue.erase(std::remove(argumentValue.begin(), argumentValue.end(), '\"'), argumentValue.end());
	identValue = argumentValue;
}

string Ident::getValue() {
	return identValue;
}

string Ident::getArgumentType() {
	return argumentType;
}

bool Ident::isIdent() {
	return true;
}

bool Ident::isInteger() {
	return false;
}

bool Ident::isSynonym() {
	return false;
}

bool Ident::isWildcard() {
	return false;
}
