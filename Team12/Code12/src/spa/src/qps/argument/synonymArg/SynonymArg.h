#pragma once

#include <string>

#include "qps/argument/IArgument.h"

using std::string;

class SynonymArg : public IArgument {
private:
	const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::SYNONYM;
	string synonymValue;

public:
	explicit SynonymArg(string argumentValue) : synonymValue(std::move(argumentValue)) {};
	string getValue() override;
	QPSStringUtils::ArgumentType getArgumentType() override;
	bool isSynonym() override;
    bool operator==(const IArgument& other) const override;
};
