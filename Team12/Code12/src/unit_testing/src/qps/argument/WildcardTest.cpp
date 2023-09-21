#include "catch.hpp"

#include "qps/argument/wildcard/Wildcard.h"

string wildcardString = "_";
string expectedWildcardValue = "_";
string wildcardArgType = "wildcard";

Wildcard wildcard = Wildcard(wildcardString);

TEST_CASE("test_wildcard_getValue") {
	string actual = wildcard.getValue();

	REQUIRE(actual == expectedWildcardValue);
}

TEST_CASE("test_wildcard_getArgumentType") {
	string actualWildcardArgType = wildcard.getArgumentType();

	REQUIRE(actualWildcardArgType == wildcardArgType);
}

TEST_CASE("test_wildcard_isIdent_false") {
	bool actualIsSynonym = wildcard.isIdent();

	REQUIRE(actualIsSynonym == false);
}

TEST_CASE("test_wildcard_isInteger_false") {
	bool actualIsSynonym = wildcard.isInteger();

	REQUIRE(actualIsSynonym == false);
}

TEST_CASE("test_wildcard_isSynonym_false") {
	bool actualIsSynonym = wildcard.isSynonym();

	REQUIRE(actualIsSynonym == false);
}

TEST_CASE("test_wildcard_isWildcard_true") {
	bool actualIsSynonym = wildcard.isWildcard();

	REQUIRE(actualIsSynonym);
}
