#pragma once

#include <string>

#include "qps/argument/IArgument.h"
#include "qps/tokenizer/PQLTokenType.h"

using std::string;

class Ident : public IArgument {
private:
	const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::IDENT;
	string identValue;

public:
	explicit Ident(const string& argumentValue, PQLTokenType tokenType);
	string getValue() override;
	QPSStringUtils::ArgumentType getArgumentType() override;
	bool isIdent() override;
	bool isInteger() override;
	bool isSynonym() override;
	bool isWildcard() override;
    bool operator==(const IArgument& other) const override;
};