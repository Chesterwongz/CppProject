#pragma once

#include <string>

#include "../IArgument.h"

using std::string;

class Integer : public IArgument {
private:
	const string argumentType = INTEGER_TYPE;
	string integerValue;
public:
	explicit Integer(string argumentValue) : integerValue(argumentValue) {};
	string getValue() override;
	string getArgumentType() override;
	virtual bool isIdent() override;
	virtual bool isInteger() override;
	virtual bool isSynonym() override;
	virtual bool isWildcard() override;
};
