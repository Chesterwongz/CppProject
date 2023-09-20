#include "catch.hpp"

#include "qps/common/QPSStringUtils.h"

string validAlphabeticSynonym = "sdfksjdnkjfn";
string validAlphanumericSynonym = "rnj324jn2k43";
string validAlphabeticIdent = "\"fkjdgn\"";
string validAlphanumericIdent = "\"j1nkn4j2n\"";
string validInteger = "234872";
string wildcard = "_";

TEST_CASE("test_isSynonym_allAlphabet_true") {
	string testSynonym = validAlphabeticSynonym;
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result);
}

TEST_CASE("test_isSynonym_alphanumeric_startWithLetter_true") {
	string testSynonym = validAlphanumericSynonym;
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result);
}

TEST_CASE("test_isSynonym_alphanumeric_startWithNumber_false") {
	string testSynonym = "1rnj324jn2k43";
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result == false);
}

TEST_CASE("test_isSynonym_containsSymbols_false_1") {
	string testSynonym = "rnj324jn2k4&3"; //contains '&'
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result == false);
}

TEST_CASE("test_isSynonym_containsSymbols_false_2") {
	string testSynonym = "rnj324j%n2k43"; //contains '%'
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result == false);
}

TEST_CASE("test_isSynonym_numeric_false") {
	string testSynonym = "239742";
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result == false);
}

TEST_CASE("test_isIdent_allAlphabet_true") {
	string testIdent = validAlphabeticIdent;
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result);
}

TEST_CASE("test_isIdent_alphanumeric_startWithLetter_true") {
	string testIdent = validAlphanumericIdent;
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result);
}

TEST_CASE("test_isIdent_alphanumeric_startWithNumber_false") {
	string testIdent = "3skdnf23j";
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result == false);
}

TEST_CASE("test_isIdent_containsSymbol_false") {
	string testIdent = validAlphanumericIdent + "#";
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result == false);
}

TEST_CASE("test_isIdent_allNumbers_false") {
	string testIdent = "\"34234\"";
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result == false);
}

TEST_CASE("test_isIdent_no_'\"'_false") {
	string testIdent = validAlphanumericSynonym;
	bool result = QPSStringUtils::isIdent(testIdent);

	REQUIRE(result == false);
}

TEST_CASE("test_isWildcard_'_'_true") {
	string testWildcard = wildcard;
	bool result = QPSStringUtils::isWildcard(testWildcard);

	REQUIRE(result);
}

TEST_CASE("test_isWildcard_not'_'_false") {
	string testWildcard = "sdf23r";
	bool result = QPSStringUtils::isWildcard(testWildcard);

	REQUIRE(result == false);
}

TEST_CASE("test_isInteger_number_true") {
	string testInteger = validInteger;
	bool result = QPSStringUtils::isInteger(testInteger);

	REQUIRE(result);
}

TEST_CASE("test_isInteger_0_true") {
	string testInteger = "0";
	bool result = QPSStringUtils::isInteger(testInteger);

	REQUIRE(result);
}

TEST_CASE("test_isInteger_01_false") {
	string testInteger = "01";
	bool result = QPSStringUtils::isInteger(testInteger);

	REQUIRE(result == false);
}

TEST_CASE("test_isInteger_alphanumeric_false") {
	string testInteger = validAlphanumericSynonym;
	bool result = QPSStringUtils::isInteger(testInteger);

	REQUIRE(result == false);
}

TEST_CASE("test_isInteger_allAlphabet_false") {
	string testInteger = validAlphabeticSynonym;
	bool result = QPSStringUtils::isInteger(testInteger);

	REQUIRE(result == false);
}

TEST_CASE("test_isInteger_withSymbols_false") {
	string testInteger = validInteger + "@";
	bool result = QPSStringUtils::isInteger(testInteger);

	REQUIRE(result == false);
}

TEST_CASE("test_isInteger_negativeInteger_false") {
	string testInteger = "-" + validInteger;
	bool result = QPSStringUtils::isInteger(testInteger);

	REQUIRE(result == false);
}

TEST_CASE("test_isEntRef_validSynonym_true") {
	string testEntRef = validAlphanumericSynonym;
	bool result = QPSStringUtils::isEntRef(testEntRef);

	REQUIRE(result);
}

TEST_CASE("test_isEntRef_validIdent_true") {
	string testEntRef = validAlphanumericIdent;
	bool result = QPSStringUtils::isEntRef(testEntRef);

	REQUIRE(result);
}

TEST_CASE("test_isEntRef_wildcard_true") {
	string testEntRef = wildcard;
	bool result = QPSStringUtils::isEntRef(testEntRef);

	REQUIRE(result);
}

TEST_CASE("test_isEntRef_validInteger_false") {
	string testEntRef = validInteger;
	bool result = QPSStringUtils::isEntRef(testEntRef);

	REQUIRE(result == false);
}

TEST_CASE("test_isStmtRef_validSynonym_true") {
	string testStmtRef = validAlphabeticSynonym;
	bool result = QPSStringUtils::isStmtRef(testStmtRef);

	REQUIRE(result);
}

TEST_CASE("test_isStmtRef_validInteger_true") {
	string testEntRef = validInteger;
	bool result = QPSStringUtils::isStmtRef(testEntRef);

	REQUIRE(result);
}

TEST_CASE("test_isStmtRef_wildcard_true") {
	string testEntRef = wildcard;
	bool result = QPSStringUtils::isStmtRef(testEntRef);

	REQUIRE(result);
}

TEST_CASE("test_isStmtRef_validIdent_false") {
	string testEntRef = validAlphanumericIdent;
	bool result = QPSStringUtils::isStmtRef(testEntRef);

	REQUIRE(result == false);
}
