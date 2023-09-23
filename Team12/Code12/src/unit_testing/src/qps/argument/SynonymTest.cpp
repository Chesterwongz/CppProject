#include "catch.hpp"

#include "qps/argument/synonym/Synonym.h"

string synonymString = "test1234";
string expectedSynonymValue = "test1234";
string synonymArgType = "synonym";

Synonym synonym = Synonym(synonymString);

TEST_CASE("test_synonym_getValue") {
	string actual = synonym.getValue();

	REQUIRE(actual == expectedSynonymValue);
}

TEST_CASE("test_synonym_getArgumentType") {
	QPSStringUtils::ArgumentType actualSynonymArgType = synonym.getArgumentType();

	REQUIRE(actualSynonymArgType == QPSStringUtils::SYNONYM);
}

TEST_CASE("test_synonym_isIdent_false") {
	bool actualIsSynonym = synonym.isIdent();

	REQUIRE(actualIsSynonym == false);
}

TEST_CASE("test_synonym_isInteger_false") {
	bool actualIsSynonym = synonym.isInteger();

	REQUIRE(actualIsSynonym == false);
}

TEST_CASE("test_synonym_isSynonym_true") {
	bool actualIsSynonym = synonym.isSynonym();

	REQUIRE(actualIsSynonym);
}

TEST_CASE("test_synonym_isWildcard_false") {
	bool actualIsSynonym = synonym.isWildcard();

	REQUIRE(actualIsSynonym == false);
}
