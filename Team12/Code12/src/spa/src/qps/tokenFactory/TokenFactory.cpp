#include <regex>
#include <iostream>

#include "TokenFactory.h"
#include "declarativeTokenFactory/DeclarativeTokenFactory.h"
#include "selectTokenFactory/SelectTokenFactory.h"

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

TokenFactoryPool TokenFactory::tokenFactories;

bool TokenFactory::isSynonym(string data) {
    std::regex synonymPattern("^[A-Za-z][A-Za-z0-9]*$");
	return std::regex_match(data, synonymPattern);
}

bool TokenFactory::isStmtRef(string data) {
    std::regex integerPattern("^[0-9]+$");
	return isSynonym(data) || data == "_" || std::regex_match(data, integerPattern);
}

bool TokenFactory::isEntRef(string data) {
	// this pattern is to check for '"' IDENT '"'
	std::regex identQuotePattern("\"[A-Za-z]([A-Za-z0-9])*\"");

	return isSynonym(data) || data == "_" || std::regex_match(data, identQuotePattern);
}

TokenFactory* TokenFactory::getOrCreateFactory(TOKENTYPES keyword) {
    switch (keyword) {
        case ENTITY:
            if (tokenFactories.find(ENTITY) == tokenFactories.end()) {
                tokenFactories[ENTITY] = std::make_unique<DeclarativeTokenFactory>();
                std::cout << "added declarativeTokenFactory to tokenFactories" << std::endl;
            }
            return tokenFactories[ENTITY].get();

        case SELECT:
            if (tokenFactories.find(SELECT) == tokenFactories.end()) {
                tokenFactories[SELECT] = std::make_unique<SelectTokenFactory>();
            }
            return tokenFactories[SELECT].get();
    }

	return nullptr;
}
