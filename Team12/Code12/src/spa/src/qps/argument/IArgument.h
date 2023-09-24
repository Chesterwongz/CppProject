#pragma once 

#include <string>

#include "qps/common/QPSStringUtils.h"
#include "common/utils/StringUtils.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

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
    virtual bool operator==(const IArgument& other) const = 0;
};
