#pragma once

#include <string>

#include "../IArgument.h"

using std::string;

class Ident : public IArgument {
private:
	const string argumentType = IDENT_TYPE;
	string identValue;

public:
	explicit Ident(string argumentValue);
	string getValue() override;
	string getArgumentType() override;

};
