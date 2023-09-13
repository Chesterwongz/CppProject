#pragma once

#include <string>

#include "../IArgument.h"

using std::string;

class Wildcard : public IArgument {
private:
	const string argumentType = "wildcard";
public:
	Wildcard(string argumentValue) : IArgument(argumentValue);
};
