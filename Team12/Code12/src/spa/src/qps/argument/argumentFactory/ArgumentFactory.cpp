#include "ArgumentFactory.h"
#include "../argumentFactoryUtil/ArgumentFactoryUtil.h"
#include "../synonym/Synonym.h"

using std::unique_ptr, std::make_unique, std::string;

unique_ptr<IArgument> ArgumentFactory::createArgument(string argument) {
	if (ArgumentFactoryUtil::isWildcard(argument)) {
		return make_unique<Wildcard>(argument);
	}

	if (ArgumentFactoryUtil::isIdent(argument) {
		return make_unique<Ident>(argument);
	}

	return make_unique<Synonym>(argument);
}