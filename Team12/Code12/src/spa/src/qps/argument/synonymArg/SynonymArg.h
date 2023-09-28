#pragma once

#include <string>

#include "qps/argument/IArgument.h"

using std::string;

class SynonymArg : public IArgument {
private:
	const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::SYNONYM;
	string synonymValue;

public:
	explicit SynonymArg(const string& argumentValue) : synonymValue(argumentValue) {};
	string getValue() override;
	QPSStringUtils::ArgumentType getArgumentType() override;
	bool isIdent() override;
	bool isInteger() override;
	bool isSynonym() override;
	bool isWildcard() override;
    bool operator==(const IArgument& other) const override;
};
