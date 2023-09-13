#pragma once 

#include <string>

using std::string;

class IArgument {

public:
	virtual string getValue() = 0;
	virtual string getArgumentType() = 0;
};