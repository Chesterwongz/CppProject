#include <catch.hpp>

#include "qps/argument/patternExp/PatternExp.h"

string patternArgString = "test + 1234";
string expectedPatternExpValue = " test 1234 + ";
string patternExpType = "patternArg";

// PatternExp patternArg = PatternExp(patternArgString);

TEST_CASE("test_patternExp_getValue") {
  PatternExp patternArg = PatternExp(patternArgString);
  string actual = patternArg.getValue();

  REQUIRE(actual == expectedPatternExpValue);
}

TEST_CASE("test_patternExp_getArgumentType") {
  PatternExp patternArg = PatternExp(patternArgString);
  QPSStringUtils::ArgumentType actualPatternExpArgType =
      patternArg.getArgumentType();

  REQUIRE(actualPatternExpArgType == QPSStringUtils::PATTERNEXP);
}

TEST_CASE("test_patternExp_isIdent_false") {
  PatternExp patternArg = PatternExp(patternArgString);
  bool actualIsPatternExp = patternArg.isIdent();

  REQUIRE(actualIsPatternExp == false);
}

TEST_CASE("test_patternExp_isInteger_false") {
  PatternExp patternArg = PatternExp(patternArgString);
  bool actualIsPatternExp = patternArg.isInteger();

  REQUIRE(actualIsPatternExp == false);
}

TEST_CASE("test_patternExp_isSynonym_false") {
  PatternExp patternArg = PatternExp(patternArgString);
  bool actualIsPatternExp = patternArg.isSynonym();

  REQUIRE(actualIsPatternExp == false);
}

TEST_CASE("test_patternExp_isWildcard_false") {
  PatternExp patternArg = PatternExp(patternArgString);
  bool actualIsPatternExp = patternArg.isWildcard();

  REQUIRE(actualIsPatternExp == false);
}

TEST_CASE("test_patternExp_isPatternExp_true") {
  PatternExp patternArg = PatternExp(patternArgString);
  bool actualIsPatternExp = patternArg.isPatternExp();

  REQUIRE(actualIsPatternExp);
}

TEST_CASE("test_patternExp_operator==_true") {
  PatternExp patternArg = PatternExp(patternArgString);
  PatternExp similarPatternExp = PatternExp(patternArgString);

  REQUIRE(patternArg == similarPatternExp);
}

TEST_CASE("test_patternExp_operator==_false") {
  PatternExp patternArg = PatternExp(patternArgString);
  PatternExp diffPatternExp = PatternExp("randomsynonym");

  REQUIRE(!(patternArg == diffPatternExp));
}
