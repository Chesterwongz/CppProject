#pragma once 

#include <string>

using std::string;

const string IDENT_TYPE = "ident";
const string SYNONYM_TYPE = "synonym";
const string WILDCARD_TYPE = "wildcard";
const string INTEGER_TYPE = "integer";

class IArgument {

public:
	virtual string getValue() = 0;
	virtual string getArgumentType() = 0;
};
