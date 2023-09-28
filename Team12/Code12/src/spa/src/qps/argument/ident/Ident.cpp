#include "Ident.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

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
