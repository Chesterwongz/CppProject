#include <memory>
#include <vector>
#include <catch.hpp>

#include "PQLParserTestUtils.h"
#include "qps/clause/patternClause/IfPatternClause.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"

TEST_CASE("Valid Pattern if (LITERAL_REF,_,_)") {
  string ifs = "ifs";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, IF_ENTITY),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  REQUIRE(true);
}

TEST_CASE("Valid Pattern if (SYNONYM,_,_)") {
  string ifs = "ifs";
  string var = "x";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, IF_ENTITY),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_SYNONYM_TOKEN, var),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  REQUIRE(true);
}

TEST_CASE("Valid Pattern if (_,_,_)") {
  string ifs = "ifs";
  string var = "x";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, IF_ENTITY),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  REQUIRE(true);
}

TEST_CASE("Invalid Pattern if (SYNONYM,_,_) - not var synonym") {
  string ifs = "ifs";
  string w = "while";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, IF_ENTITY),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, WHILE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, w),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, w),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_AS(parseToQuery(tokenList),
                    QPSSemanticError);
}

TEST_CASE("Invalid Pattern if (SYNONYM,_,LITERAL_REF)") {
  string ifs = "ifs";
  string w = "while";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, IF_ENTITY),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, w),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, w),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "hello"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_MATCHES(
      parseToQuery(tokenList),
      QPSSyntaxError,
      Catch::Message(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT));
}

TEST_CASE("Invalid Pattern if (SYNONYM,_)") {
  string ifs = "ifs";
  string w = "while";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, IF_ENTITY),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, w),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, w),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_AS(
      parseToQuery(tokenList),
      QPSSemanticError);
}

TEST_CASE("Valid Pattern not if (_,_,_)") {
  string ifs = "ifs";
  string var = "x";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, IF_ENTITY),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  REQUIRE(true);
}

TEST_CASE("Valid Pattern not if (_,_,_) - not as outer synonym") {
  string ifs = "not";
  string var = "x";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, IF_ENTITY),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ifs),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  REQUIRE(true);
}
