#include <catch.hpp>

#include "qps/common/Keywords.h"
#include "qps/common/QPSStringUtils.h"

string validAlphabeticSynonym = "sdfksjdnkjfn";
string validAlphanumericSynonym = "rnj324jn2k43";
string validAlphabeticIdent = "fkjdgn";
string validAlphanumericIdent = "j1nkn4j2n";
string validInteger = "234872";

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
  string testSynonym = "rnj324jn2k4&3";  // contains '&'
  bool result = QPSStringUtils::isSynonym(testSynonym);

  REQUIRE(result == false);
}

TEST_CASE("test_isSynonym_containsSymbols_false_2") {
  string testSynonym = "rnj324j%n2k43";  // contains '%'
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
  string testIdent = "34234";
  bool result = QPSStringUtils::isIdent(testIdent);

  REQUIRE(result == false);
}

TEST_CASE("test_isWildcard_'_'_true") {
  string testWildcard = WILDCARD_KEYWORD;
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

TEST_CASE("test_convertToRPN_basicAddition") {
  string expression = "3 + 4";
  string expected = " 3 4 + ";
  string actual = QPSStringUtils::convertToRPN(expression);

  REQUIRE(actual == expected);
}

TEST_CASE("test_convertToRPN_basicSubtraction") {
  string expression = "3 - 5";
  string expected = " 3 5 - ";
  string actual = QPSStringUtils::convertToRPN(expression);

  REQUIRE(actual == expected);
}

TEST_CASE("test_convertToRPN_basicMultiplication") {
  string expression = "4 * 10";
  string expected = " 4 10 * ";
  string actual = QPSStringUtils::convertToRPN(expression);

  REQUIRE(actual == expected);
}

TEST_CASE("test_convertToRPN_basicDivision") {
  string expression = "6 / 2";
  string expected = " 6 2 / ";
  string actual = QPSStringUtils::convertToRPN(expression);

  REQUIRE(actual == expected);
}

TEST_CASE("test_convertToRPN_parenthesis") {
  string expression = "6 / (2 + 3)";
  string expected = " 6 2 3 + / ";
  string actual = QPSStringUtils::convertToRPN(expression);

  REQUIRE(actual == expected);
}

TEST_CASE("test_convertToRPN_nestedParenthesis") {
  string expression = "((3 + 4) * (8 - 2)) / (7 - 1)";
  string expected = " 3 4 + 8 2 - * 7 1 - / ";
  string actual = QPSStringUtils::convertToRPN(expression);

  REQUIRE(actual == expected);
}

TEST_CASE("test_convertToRPN_withVariableNames") {
  string expression = "testVar1 - testVar2 * 5";
  string expected = " testVar1 testVar2 5 * - ";
  string actual = QPSStringUtils::convertToRPN(expression);

  REQUIRE(actual == expected);
}

TEST_CASE("test_convertToRPN_withVariableNames_nestedParenthesis") {
  string expression = "((myVar + 4) * (88 - test1)) / (7 - 1)";
  string expected = " myVar 4 + 88 test1 - * 7 1 - / ";
  string actual = QPSStringUtils::convertToRPN(expression);

  REQUIRE(actual == expected);
}

TEST_CASE("test_convertToRPN_weirdSpacing") {
  string expression = "a + b -c * d /  e %f";
  string expected = " a b + c d * e / f % - ";
  string actual = QPSStringUtils::convertToRPN(expression);

  REQUIRE(actual == expected);
}
