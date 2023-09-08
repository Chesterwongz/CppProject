#include "../src/spa/src/qps/tokenFactory/TokenFactory.h"
#include "../src/spa/src/qps/tokenFactory/declarativeTokenFactory/DeclarativeTokenFactory.h"

#include "catch.hpp"

TEST_CASE("Add declarative factory test") {
	DeclarativeTokenFactory* dtf = dynamic_cast<DeclarativeTokenFactory *>(TokenFactory::getOrCreateFactory("stmt"));
	bool res = TokenFactory::tokenFactories.find(DECLARATIVE) != TokenFactory::tokenFactories.end();
	REQUIRE(res);
}
