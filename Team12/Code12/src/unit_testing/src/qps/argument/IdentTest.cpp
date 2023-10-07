// TEMP_CATCH_INCLUDE

#include "qps/argument/ident/Ident.h"

string identString = "test";
string expectedIdentValue = "test";
string identArgType = "ident";

Ident ident = Ident(identString);

TEST_CASE("test_ident_getValue") {
  // TODO(QPS): update ident constructor
  // this one will fail for now bcos ident constructor doesnt remove '\"'
  string actual = ident.getValue();

  REQUIRE(actual == expectedIdentValue);
}

TEST_CASE("test_ident_getArgumentType") {
  QPSStringUtils::ArgumentType actualIdentArgType = ident.getArgumentType();

  REQUIRE(actualIdentArgType == QPSStringUtils::IDENT);
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

TEST_CASE("test_ident_operator==_true") {
  Ident similarIdent = Ident(identString);

  REQUIRE(ident == similarIdent);
}

TEST_CASE("test_ident_operator==_false") {
  Ident diffIdent = Ident("randomstring");

  REQUIRE(!(ident == diffIdent));
}
