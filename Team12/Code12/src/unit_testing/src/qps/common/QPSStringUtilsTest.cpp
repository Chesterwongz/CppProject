#include "catch.hpp"

#include "qps/common/QPSStringUtils.h"


TEST_CASE("test_isSynonym_allAlphabet_valid") {
	string testSynonym = "sdfksjdnkjfn";
	bool result = QPSStringUtils::isSynonym(testSynonym);

	REQUIRE(result);
}

TEST_CASE("test_isSynonym_alphanumeric_startWithLetter_valid") {
	string testSynonym = "rnj324jn2k43";
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
