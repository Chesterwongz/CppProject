#pragma once

#include <string>

#include "qps/argument/IArgument.h"

using std::string;

class Integer : public IArgument {
private:
	const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::INTEGER;
	string integerValue;
public:
	explicit Integer(string argumentValue);
	string getValue() override;
	QPSStringUtils::ArgumentType getArgumentType() override;
	virtual bool isIdent() override;
	virtual bool isInteger() override;
	virtual bool isSynonym() override;
	virtual bool isWildcard() override;
};
