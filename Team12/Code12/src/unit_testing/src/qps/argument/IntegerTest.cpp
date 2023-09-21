#include "catch.hpp"

#include "qps/argument/integer/Integer.h"

string integerString = "1234";
string expectedIntegerValue = "1234";
string integerArgType = "integer";

Integer integer = Integer(integerString);

TEST_CASE("test_integer_getValue") {
	string actual = integer.getValue();

	REQUIRE(actual == expectedIntegerValue);
}

TEST_CASE("test_integer_getArgumentType") {
	string actualIdentArgType = integer.getArgumentType();

	REQUIRE(actualIdentArgType == integerArgType);
}

TEST_CASE("test_integer_isIdent_false") {
	bool actualIsInteger = integer.isIdent();

	REQUIRE(actualIsInteger == false);
}

TEST_CASE("test_integer_isInteger_true") {
	bool actualIsInteger = integer.isInteger();

	REQUIRE(actualIsInteger);
}

TEST_CASE("test_integer_isSynonym_false") {
	bool actualIsInteger = integer.isSynonym();

	REQUIRE(actualIsInteger == false);
}

TEST_CASE("test_integer_isWildcard_false") {
	bool actualIsInteger = integer.isWildcard();

	REQUIRE(actualIsInteger == false);
}
