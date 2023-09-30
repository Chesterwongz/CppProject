#include "ArgumentFactory.h"

using std::unique_ptr, std::make_unique, std::string;

unique_ptr<AbstractArgument> ArgumentFactory::createArgument(string& argument) {
	if (QPSStringUtils::isWildcard(argument)) {
		return make_unique<Wildcard>();
	} 

	if (QPSStringUtils::isIdent(argument)) {
		// remove '\"' from value
		// create new string so as to not modify reference
		string identString = argument;
		identString.erase(std::remove(identString.begin(), identString.end(), '\"'), identString.end());
		return make_unique<Ident>(identString);
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

unique_ptr<Ident> ArgumentFactory::createIdentArgument(const string& argumentValue) {
	return make_unique<Ident>(argumentValue);
}

unique_ptr<Integer> ArgumentFactory::createIntegerArgument(const string& argumentValue) {
	return make_unique<Integer>(argumentValue);
}

unique_ptr<Wildcard> ArgumentFactory::createWildcardArgument() {
	return make_unique<Wildcard>();
}
