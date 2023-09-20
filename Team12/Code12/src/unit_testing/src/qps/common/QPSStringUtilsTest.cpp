#include "catch.hpp"

#include "qps/common/QPSStringUtils.h"

string validAlphabeticSynonym = "sdfksjdnkjfn";
string validAlphanumericSynonym = "rnj324jn2k43";
string validAlphabeticIdent = "\"fkjdgn\"";
string validAlphanumericIdent = "\"j1nkn4j2n\"";

TEST_CASE("test_isSynonym_allAlphabet_valid") {
	string testSynonym = validAlphabeticSynonym;
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result);
}

TEST_CASE("test_isSynonym_alphanumeric_startWithLetter_valid") {
	string testSynonym = validAlphanumericSynonym;
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result);
}

TEST_CASE("test_isSynonym_alphanumeric_startWithNumber_invalid") {
	string testSynonym = "1rnj324jn2k43";
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result == false);
}

TEST_CASE("test_isSynonym_containsSymbols_invalid_1") {
	string testSynonym = "rnj324jn2k4&3"; //contains '&'
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result == false);
}

TEST_CASE("test_isSynonym_containsSymbols_invalid_2") {
	string testSynonym = "rnj324j%n2k43"; //contains '%'
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result == false);
}

TEST_CASE("test_isSynonym_numeric_invalid") {
	string testSynonym = "239742";
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result == false);
}

TEST_CASE("test_isIdent_allAlphabet_valid") {
	string testIdent = validAlphabeticIdent;
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result);
}

TEST_CASE("test_isIdent_alphanumeric_startWithLetter_valid") {
	string testIdent = validAlphanumericIdent;
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result);
}

TEST_CASE("test_isIdent_alphanumeric_startWithNumber_invalid") {
	string testIdent = "3skdnf23j";
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result == false);
}

TEST_CASE("test_isIdent_containsSymbol_invalid") {
	string testIdent = validAlphanumericIdent + "#";
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result == false);
}

TEST_CASE("test_isIdent_allNumbers_invalid") {
	string testIdent = "\"34234\"";
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result == false);
}

TEST_CASE("test_isIdent_no_'\"'_invalid") {
	string testIdent = validAlphanumericSynonym;
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result == false);
}

TEST_CASE("test_isEntRef_validSynonym_valid") {
	string testEntRef = validAlphanumericSynonym;
	bool result = QPSStringUtils::isEntRef(testEntRef);

	REQUIRE(result);
}
