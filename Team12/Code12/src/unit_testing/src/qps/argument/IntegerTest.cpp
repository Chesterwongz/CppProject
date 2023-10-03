#include <catch.hpp>

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
  QPSStringUtils::ArgumentType actualIntegerArgType = integer.getArgumentType();

  REQUIRE(actualIntegerArgType == QPSStringUtils::INTEGER);
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

TEST_CASE("test_integer_operator==_true") {
  Integer similarInteger = Integer(integerString);

  REQUIRE(integer == similarInteger);
}

TEST_CASE("test_integer_operator==_false") {
  string randomNum = "29384";
  Integer diffInteger = Integer(randomNum);

  REQUIRE(!(integer == diffInteger));
}
