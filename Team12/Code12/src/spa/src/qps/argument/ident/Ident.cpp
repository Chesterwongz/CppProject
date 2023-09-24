#include "Ident.h"

Ident::Ident(const string& argumentValue, PQLTokenType tokenType) {
	if (tokenType != PQL_LITERAL_REF_TOKEN) {
		throw QPSInvalidQueryException("argumentValue is not PQL_LITERAL_REF_TOKEN");
	}

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
