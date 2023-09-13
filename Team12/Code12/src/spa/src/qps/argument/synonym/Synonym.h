#pragma once

#include <string>

#include "../IArgument.h"

using std::string;

class Synonym : public IArgument {
private:
	const string argumentType = "synonym";
public:
	Synonym(string argumentValue) : IArgument(argumentValue);
};