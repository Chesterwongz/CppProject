#include "TNode.h"

#include "catch.hpp"
#include "../../spa/src/qps/tokeniser/TokeniserUtil.h"

using namespace std;


TEST_CASE("Test_isDesignEntity_stmt_true") {

	TokeniserUtil tokeniserUtil;
	std::string word = "stmt";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == true);
}

TEST_CASE("Test_isDesignEntity_stMt_false") {
	// test case sensitivity

	TokeniserUtil tokeniserUtil;

	std::string word = "stMt";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == false);
}

TEST_CASE("Test_isDesignEntity_read_true") {

	TokeniserUtil tokeniserUtil;

	std::string word = "read";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == true);
}

TEST_CASE("Test_isDesignEntity_print_true") {

	TokeniserUtil tokeniserUtil;

	std::string word = "print";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == true);
}

TEST_CASE("Test_isDesignEntity_call_true") {

	TokeniserUtil tokeniserUtil;

	std::string word = "call";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == true);
}

TEST_CASE("Test_isDesignEntity_while_true") {

	TokeniserUtil tokeniserUtil;

	std::string word = "while";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == true);
}

TEST_CASE("Test_isDesignEntity_if_true") {

	TokeniserUtil tokeniserUtil;

	std::string word = "if";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == true);
}

TEST_CASE("Test_isDesignEntity_assign_true") {

	TokeniserUtil tokeniserUtil;

	std::string word = "assign";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == true);
}

TEST_CASE("Test_isDesignEntity_variable_true") {

	TokeniserUtil tokeniserUtil;

	std::string word = "variable";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == true);
}

TEST_CASE("Test_isDesignEntity_constant_true") {

	TokeniserUtil tokeniserUtil;

	std::string word = "constant";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == true);
}

TEST_CASE("Test_isDesignEntity_procedure_true") {

	TokeniserUtil tokeniserUtil;

	std::string word = "procedure";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == true);
}

TEST_CASE("Test_isDesignEntity_random_false") {

	TokeniserUtil tokeniserUtil;

	std::string word = "randpm";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == false);
}

TEST_CASE("Test_isDesignEntity_123_true") {

	TokeniserUtil tokeniserUtil;

	std::string word = "123";
	bool result = tokeniserUtil.isDesignEntity(word);

	REQUIRE(result == false);
}
