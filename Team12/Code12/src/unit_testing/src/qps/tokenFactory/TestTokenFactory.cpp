#include "../../../../spa/src/qps/tokenFactory/TokenFactory.h"

#include "catch.hpp"

TEST_CASE("Add declarative factory test") {
	TokenFactory tf;

	unique_ptr<TokenFactory> declarativeFactory = tf.createOrAddFactoryToPool("stmt");
	
	REQUIRE(tf.tokenFactories.find(DECLARATIVE) != tf.tokenFactories.end());
}
