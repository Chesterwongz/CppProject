#include "ArgumentFactory.h"
#include "../synonym/Synonym.h"
#include "../../common/QPSStringUtils.h"
#include "../wildcard/Wildcard.h"
#include "../Ident/Ident.h"
#include "../integer/Integer.h"

using std::unique_ptr, std::make_unique, std::string;

unique_ptr<IArgument> ArgumentFactory::createArgument(string argument) {
	if (QPSStringUtils::isWildcard(argument)) {
		return make_unique<Wildcard>();
	} 

	if (QPSStringUtils::isIdent(argument)) {
		return make_unique<Ident>(argument);
	}

	if (QPSStringUtils::isSynonym(argument)) {
		return make_unique<Synonym>(argument);
	}
	
	if (QPSStringUtils::isInteger(argument)) {
		return make_unique<Integer>(argument);
	}

	return nullptr;
}

unique_ptr<Synonym> ArgumentFactory::createSynonymArgument(string argumentValue) {
	return make_unique<Synonym>(argumentValue);
}

unique_ptr<Ident> ArgumentFactory::createIdentArgument(string argumentValue) {
	return make_unique<Ident>(argumentValue);
}

unique_ptr<Integer> ArgumentFactory::createIntegerArgument(string argumentValue) {
	return make_unique<Integer>(argumentValue);
}

unique_ptr<Wildcard> ArgumentFactory::createWildcardArgument() {
	return make_unique<Wildcard>();
}
