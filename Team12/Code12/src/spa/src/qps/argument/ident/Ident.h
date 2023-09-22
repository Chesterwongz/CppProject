#pragma once

#include <string>

#include "../IArgument.h"

using std::string;

class Ident : public IArgument {
private:
	const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::IDENT;
	string identValue;

public:
	explicit Ident(string argumentValue);
	string getValue() override;
	QPSStringUtils::ArgumentType getArgumentType() override;
	virtual bool isIdent() override;
	virtual bool isInteger() override;
	virtual bool isSynonym() override;
	virtual bool isWildcard() override;
};
