#pragma once 

#include <string>

#include "qps/common/QPSStringUtils.h"

using std::string;

class IArgument {
public:

	virtual string getValue() = 0;
	virtual QPSStringUtils::ArgumentType getArgumentType() = 0;
	virtual bool isIdent() = 0;
	virtual bool isInteger() = 0;
	virtual bool isSynonym() = 0;
	virtual bool isWildcard() = 0;

	virtual ~IArgument() = default;
};
