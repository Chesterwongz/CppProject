#pragma once 

#include <string>

using std::string;

class IArgument {
protected:
	string value;
public:
	explicit IArgument(string argumentValue) : value(argumentValue);

	virtual string getValue() = 0;
	virtual string getArgumentType() = 0;
};