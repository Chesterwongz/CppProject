#pragma once

#include <string>

#include "qps/argument/IArgument.h"

using std::string;

class Integer : public IArgument {
private:
	const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::INTEGER;
	string integerValue;
public:
	explicit Integer(const string& argumentValue) : integerValue(argumentValue) {};
	string getValue() override;
	QPSStringUtils::ArgumentType getArgumentType() override;
	bool isIdent() override;
	bool isInteger() override;
	bool isSynonym() override;
	bool isWildcard() override;
    virtual bool operator==(const IArgument& other) const override;
};
