#include "Ident.h"

Ident::Ident(const string& argumentValue) {
	// TODO: check its ident and remove '\"'
	//if (!QPSStringUtils::isIdent(argumentValue)) {
	//	throw std::runtime_error("argumentValue is not an ident");
	//}

	//// remove '\"' from value
	//argumentValue.erase(std::remove(argumentValue.begin(), argumentValue.end(), '\"'), argumentValue.end());
	identValue = argumentValue;
}

string Ident::getValue() {
	return identValue;
}

QPSStringUtils::ArgumentType Ident::getArgumentType() {
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

bool Ident::operator==(const IArgument& other) const {
	const auto* otherIdent = dynamic_cast<const Ident*>(&other);
	if (!otherIdent) return false;

	return this->identValue == otherIdent->identValue;
}
