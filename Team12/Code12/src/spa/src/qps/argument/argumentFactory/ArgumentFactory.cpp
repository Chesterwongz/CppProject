#include "ArgumentFactory.h"
#include "../synonym/Synonym.h"
#include "../../common/QPSStringUtils.h"
#include "../wildcard/Wildcard.h"
#include "../Ident/Ident.h"
#include "../integer/Integer.h"

using std::unique_ptr, std::make_unique, std::string;

unique_ptr<IArgument> ArgumentFactory::createArgument(string argument) {
	if (QPSStringUtils::isWildcard(argument)) {
		return make_unique<Wildcard>(argument);
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