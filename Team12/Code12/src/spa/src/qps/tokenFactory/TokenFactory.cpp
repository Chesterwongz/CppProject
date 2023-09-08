#include <regex>

#include "TokenFactory.h"
#include "declarativeTokenFactory/DeclarativeTokenFactory.h"
#include "../../common/utils/StringUtils.h";

set<string> TokenFactory::entities = {
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
}

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

unique_ptr<TokenFactory> TokenFactory::createOrAddFactoryToPool(string keyword) {
	if (entities.find(keyword) != entities.end()) 
	{
		if (tokenFactories.find(DECLARATIVE) == tokenFactories.end()) {
			tokenFactories[DECLARATIVE] = std::make_unique<DeclarativeTokenFactory>();
		}
		return tokenFactories[DECLARATIVE];
	}

	return nullptr;
}