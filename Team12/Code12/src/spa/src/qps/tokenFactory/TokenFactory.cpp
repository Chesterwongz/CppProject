#include <regex>
#include <iostream>

#include "TokenFactory.h"
#include "declarativeTokenFactory/DeclarativeTokenFactory.h"
#include "selectTokenFactory/SelectTokenFactory.h"
#include "suchThatTokenFactory/SuchThatTokenFactory.h"

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
        case SUCH_THAT:
            if (tokenFactories.find(SUCH_THAT) == tokenFactories.end()) {
                tokenFactories[SUCH_THAT] = std::make_unique<SuchThatTokenFactory>();
            }
            return tokenFactories[SUCH_THAT].get();
    }

	return nullptr;
}
