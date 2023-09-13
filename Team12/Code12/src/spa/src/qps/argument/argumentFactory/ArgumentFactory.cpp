#include "ArgumentFactory.h"
#include "../synonym/Synonym.h"
#include "../../../common/utils/StringUtils.h"
#include "../wildcard/Wildcard.h"
#include "../Ident/Ident.h"


using std::unique_ptr, std::make_unique, std::string;

unique_ptr<IArgument> ArgumentFactory::createArgument(string argument) {
	if (StringUtils::isWildcard(argument)) {
		return make_unique<Wildcard>(argument);
	} 

	if (StringUtils::isIdent(argument)) {
		return make_unique<Ident>(argument);
	}

	if (StringUtils::isSynonym(argument)) {
		return make_unique<Synonym>(argument);
	}
	
	return nullptr;
}