#pragma once

#include <string>

#include "../IArgument.h"

using std::string;

class Ident : public IArgument {
private:
	const string argumentType = "ident";
	string identValue;
public:
	Ident(string argumentValue) : identValue(argumentValue) {
		argumentValue.erase(std::remove(argumentValue.begin(), argumentValue.end(), '\"'), argumentValue.end());
		identValue = argumentValue;
	};
	string getValue() override;
	string getArgumentType() override;

};
