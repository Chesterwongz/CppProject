#include <string>
#include "SynonymArg.h"

SynonymArg::SynonymArg(const string& argumentValue) {
	if (!QPSStringUtils::isSynonym(argumentValue)) {
		throw std::runtime_error("argumentValue is not a synonymArg");
	}

	synonymValue = argumentValue;
}

string SynonymArg::getValue() {
	return synonymValue;
}

QPSStringUtils::ArgumentType SynonymArg::getArgumentType() {
	return argumentType;
}

bool SynonymArg::isIdent() {
	return false;
}

bool SynonymArg::isInteger() {
	return false;
}

bool SynonymArg::isSynonym() {
	return true;
}

bool SynonymArg::isWildcard() {
	return false;
}
