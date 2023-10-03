#pragma once

#include <string>

#include "qps/argument/AbstractArgument.h"
#include "qps/tokenizer/PQLTokenType.h"

using std::string;

class Ident : public AbstractArgument {
private:
	const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::IDENT;
	string identValue;

public:
	explicit Ident(string argumentValue) : identValue(std::move(argumentValue)) {};
	string getValue() override;
	QPSStringUtils::ArgumentType getArgumentType() override;
	bool isIdent() override;
    bool operator==(const AbstractArgument& other) const override;
};
