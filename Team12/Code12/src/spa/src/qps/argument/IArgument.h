#pragma once 

#include <string>

#include "qps/common/QPSStringUtils.h"
#include "common/utils/StringUtils.h"

using std::string;

class IArgument {
public:
	virtual string getValue() = 0;
	virtual QPSStringUtils::ArgumentType getArgumentType() = 0;
	virtual bool isIdent() { return false; }
	virtual bool isInteger() { return false; }
	virtual bool isSynonym() { return false; }
	virtual bool isWildcard() { return false; }
    virtual ~IArgument() = default;
    virtual bool operator==(const IArgument& other) const = 0;
};
