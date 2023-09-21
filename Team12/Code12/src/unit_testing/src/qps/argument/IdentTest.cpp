#include "catch.hpp"

#include "qps/argument/ident/Ident.h"

string identString = "\"test\"";
string expectedIdentValue = "test";
string identArgType = "ident";

Ident ident = Ident(identString);

TEST_CASE("test_ident_getValue") {
	string actual = ident.getValue();

	REQUIRE(actual == expectedIdentValue);
}

TEST_CASE("test_ident_getArgumentType") {
	string actualIdentArgType = ident.getArgumentType();

	REQUIRE(actualIdentArgType == identArgType);
}

TEST_CASE("test_ident_isIdent_true") {
	bool actualIsIdent = ident.isIdent();

	REQUIRE(actualIsIdent);
}

TEST_CASE("test_ident_isInteger_false") {
	bool actualIsIdent = ident.isInteger();

	REQUIRE(actualIsIdent == false);
}

TEST_CASE("test_ident_isSynonym_false") {
	bool actualIsIdent = ident.isSynonym();

	REQUIRE(actualIsIdent == false);
}

TEST_CASE("test_ident_isWildcard_false") {
	bool actualIsIdent = ident.isWildcard();

	REQUIRE(actualIsIdent == false);
}
