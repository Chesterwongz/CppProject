#include <regex>
#include <iostream>

#include "TokenFactory.h"
#include "declarativeTokenFactory/DeclarativeTokenFactory.h"

const set<string> TokenFactory::entities = {
	"stmt",
	"read",
	"print",
	"call",
	"while",
	"if",
	"assign",
	"variable",
	"constant",
	"procedure"
};

const bool TokenFactory::isSynonym(string data) {
	return StringUtils::isName(data);
}

const bool TokenFactory::isStmtRef(string data) {
	return isSynonym(data) || data == "_" || StringUtils::isInteger(data);
}

const bool TokenFactory::isEntRef(string data) {
	// this pattern is to check for '"' IDENT '"'
	std::regex identQuotePattern("\"[A-Za-z]([A-Za-z0-9])*\"");

	return isSynonym(data) || data == "_" || std::regex_match(data, identQuotePattern);
}

TokenFactory* TokenFactory::getOrCreateFactory(string keyword) {
	if (entities.find(keyword) != entities.end()) 
	{
		if (tokenFactories.find(DECLARATIVE) == tokenFactories.end()) {
			tokenFactories[DECLARATIVE] = std::make_unique<DeclarativeTokenFactory>();
            std::cout << "added declarativeTokenFactory to tokenFactories" << std::endl;
		}
		return tokenFactories[DECLARATIVE].get();
	}

	return nullptr;
}