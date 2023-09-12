#include "../src/spa/src/qps/tokenFactory/TokenFactory.h"
#include "../src/spa/src/qps/tokenFactory/declarativeTokenFactory/DeclarativeTokenFactory.h"

#include "catch.hpp"

TEST_CASE("Add declarative factory test") {
	DeclarativeTokenFactory* dtf = dynamic_cast<DeclarativeTokenFactory *>(TokenFactory::getOrCreateFactory(ENTITY));
	bool res = TokenFactory::tokenFactories.find(ENTITY) != TokenFactory::tokenFactories.end();
	REQUIRE(res);
}
