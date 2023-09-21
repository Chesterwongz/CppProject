#pragma once 

#include <string>

using std::string;

class IArgument {
protected:
	const string IDENT_TYPE = "ident";
	const string SYNONYM_TYPE = "synonym";
	const string WILDCARD_TYPE = "wildcard";
	const string INTEGER_TYPE = "integer";

public:

	virtual string getValue() = 0;
	virtual string getArgumentType() = 0;
	virtual bool isIdent() = 0;
	virtual bool isInteger() = 0;
	virtual bool isSynonym() = 0;
	virtual bool isWildcard() = 0;
};
