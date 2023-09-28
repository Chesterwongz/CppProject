#include "catch.hpp"

#include "qps/argument/argumentFactory/ArgumentFactory.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

string testWildcard = "_";
string testSynonym = "test1234";
string testIdent = "\"test4567\"";
string testInteger = "4321";
string testInvalid = "$234(NE";

using std::unique_ptr;

TEST_CASE("test_createArgument_wildcard") {
	unique_ptr<IArgument> arg = ArgumentFactory::createArgument(testWildcard);

	REQUIRE(arg->isIdent() == false);
	REQUIRE(arg->isInteger() == false);
	REQUIRE(arg->isSynonym() == false);
	REQUIRE(arg->isWildcard());
	REQUIRE(arg->getValue() == "_");
}

TEST_CASE("test_createArgument_synonym") {
	unique_ptr<IArgument> arg = ArgumentFactory::createArgument(testSynonym);

	REQUIRE(arg->isIdent() == false);
	REQUIRE(arg->isInteger() == false);
	REQUIRE(arg->isSynonym());
	REQUIRE(arg->isWildcard() == false);
}

TEST_CASE("test_createArgument_ident") {
	unique_ptr<IArgument> arg = ArgumentFactory::createArgument(testIdent);

	REQUIRE(arg->isIdent());
	REQUIRE(arg->isInteger() == false);
	REQUIRE(arg->isSynonym() == false);
	REQUIRE(arg->isWildcard() == false);
}

TEST_CASE("test_createArgument_integer") {
	unique_ptr<IArgument> arg = ArgumentFactory::createArgument(testInteger);

	REQUIRE(arg->isIdent() == false);
	REQUIRE(arg->isInteger());
	REQUIRE(arg->isSynonym() == false);
	REQUIRE(arg->isWildcard() == false);
}

TEST_CASE("test_createArgument_invalidString_returnsNullPtr") {
	unique_ptr<IArgument> arg = ArgumentFactory::createArgument(testInvalid);

	REQUIRE(arg == nullptr);
}

TEST_CASE("test_createWildcardArgument") {
	unique_ptr<IArgument> arg = ArgumentFactory::createWildcardArgument();

	REQUIRE(arg->isIdent() == false);
	REQUIRE(arg->isInteger() == false);
	REQUIRE(arg->isSynonym() == false);
	REQUIRE(arg->isWildcard());
	REQUIRE(arg->getValue() == "_");
}

TEST_CASE("test_createSynonymArgument") {
	unique_ptr<IArgument> arg = ArgumentFactory::createSynonymArgument(testSynonym);

	REQUIRE(arg->isIdent() == false);
	REQUIRE(arg->isInteger() == false);
	REQUIRE(arg->isSynonym());
	REQUIRE(arg->isWildcard() == false);
}

TEST_CASE("test_createIdentArgument") {
	unique_ptr<IArgument> arg = ArgumentFactory::createIdentArgument(testIdent);

	REQUIRE(arg->isIdent());
	REQUIRE(arg->isInteger() == false);
	REQUIRE(arg->isSynonym() == false);
	REQUIRE(arg->isWildcard() == false);
}
