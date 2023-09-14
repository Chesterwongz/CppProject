#pragma once 

#include <string>

using std::string;

class IArgument {

public:
	const string IDENT_TYPE = "ident";
	const string SYNONYM_TYPE = "synonym";
	const string WILDCARD_TYPE = "wildcard";

	virtual string getValue() = 0;
	virtual string getArgumentType() = 0;
};