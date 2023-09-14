#pragma once

#include <string>

#include "../IArgument.h"

using std::string;

class Wildcard : public IArgument {
private:
	const string argumentType = WILDCARD_TYPE;
	string wildcardValue;

public:
	explicit Wildcard(string argumentValue) : wildcardValue(argumentValue) {};
	string getValue() override;
	string getArgumentType() override;
};
