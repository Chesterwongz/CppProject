#include "ArgumentFactory.h"
#include "../argumentFactoryUtil/ArgumentFactoryUtil.h"
#include "../synonym/Synonym.h"
#include "../../../common/utils/StringUtils.h"

using std::unique_ptr, std::make_unique, std::string;

unique_ptr<IArgument> ArgumentFactory::createArgument(string argument) {
	if (StringUtils::isWildcard(argument)) {
		return make_unique<Wildcard>(argument);
	}

	if (StringUtils::isIdent(argument) {
		return make_unique<Ident>(argument);
	}

	if (StringUtils::isSynonym) {
		return make_unique<Synonym>(argument);
	}
	
	return nullptr;
}