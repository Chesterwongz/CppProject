#pragma once

#include <string>

#include "qps/argument/IArgument.h"
#include "common/utils/StringUtils.h"
using std::string;

class Wildcard : public IArgument {
private:
	const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::WILDCARD;
	string wildcardValue = StringUtils::WILDCARD;

public:
	explicit Wildcard() {};
	string getValue() override;
	QPSStringUtils::ArgumentType getArgumentType() override;
	virtual bool isIdent() override;
	virtual bool isInteger() override;
	virtual bool isSynonym() override;
	virtual bool isWildcard() override;
};
