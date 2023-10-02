#pragma once 

#include <string>

#include "qps/common/QPSStringUtils.h"
#include "common/utils/StringUtils.h"

using std::string;

class AbstractArgument {
public:
	virtual string getValue() = 0;
	virtual QPSStringUtils::ArgumentType getArgumentType() = 0;
	virtual bool isIdent();
	virtual bool isInteger();
	virtual bool isSynonym();
	virtual bool isWildcard();
    virtual ~AbstractArgument() = default;
    virtual bool operator==(const AbstractArgument& other) const = 0;
};
