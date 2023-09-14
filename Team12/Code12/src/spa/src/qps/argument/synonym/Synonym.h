#pragma once

#include <string>

#include "../IArgument.h"

using std::string;

class Synonym : public IArgument {
private:
	const string argumentType = SYNONYM_TYPE;
	string synonymValue;

public:
	explicit Synonym(string argumentValue) : synonymValue(argumentValue) {};
	string getValue() override;
	string getArgumentType() override;
};
