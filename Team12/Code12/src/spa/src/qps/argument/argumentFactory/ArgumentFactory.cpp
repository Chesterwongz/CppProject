#include "ArgumentFactory.h"

using std::unique_ptr, std::make_unique, std::string;

unique_ptr<IArgument> ArgumentFactory::createArgument(string& argument) {
	if (QPSStringUtils::isWildcard(argument)) {
		return make_unique<Wildcard>();
	} 

	if (QPSStringUtils::isIdent(argument)) {
		// remove '\"' from value
		argument.erase(std::remove(argument.begin(), argument.end(), '\"'), argument.end());
		return make_unique<Ident>(argument, PQL_LITERAL_REF_TOKEN);
	}

	if (QPSStringUtils::isSynonym(argument)) {
		return make_unique<SynonymArg>(argument);
	}
	
	if (QPSStringUtils::isInteger(argument)) {
		return make_unique<Integer>(argument);
	}

	return nullptr;
}

unique_ptr<SynonymArg> ArgumentFactory::createSynonymArgument(const string& argumentValue) {
	return make_unique<SynonymArg>(argumentValue);
}

unique_ptr<Ident> ArgumentFactory::createIdentArgument(const string& argumentValue, PQLTokenType tokenType) {
	return make_unique<Ident>(argumentValue, tokenType);
}

unique_ptr<Integer> ArgumentFactory::createIntegerArgument(const string& argumentValue) {
	return make_unique<Integer>(argumentValue);
}

unique_ptr<Wildcard> ArgumentFactory::createWildcardArgument() {
	return make_unique<Wildcard>();
}
