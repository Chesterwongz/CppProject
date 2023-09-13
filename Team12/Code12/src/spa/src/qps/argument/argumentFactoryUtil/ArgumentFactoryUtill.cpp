#include <string>
#include "ArgumentFactoryUtil.h"

using std::string;

bool ArgumentFactoryUtil::isSynonym(string argument) {
	return argument.find(doublequotes) == string::npos;
}

bool ArgumentFactoryUtil::isIdent(string argument) {
	// check if argument starts and ends with '"'
	if (argument.length() < 2) {
		return false;
	}
	return argument.front() == ArgumentFactoryUtils::doublequotes && 
		argument.back() == doublequotes;
}

bool ArgumentFactoryUtil::isWildcard(string argument) {
	return argument == wildcard;
}
