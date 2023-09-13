#pragma once

#include <string>

#include "../IArgument.h"

using std::string;

class Ident : public IArgument {
private:
	const string argumentType = "ident";
public:
	Ident(string argumentValue) : IArgument(argumentValue);
};
