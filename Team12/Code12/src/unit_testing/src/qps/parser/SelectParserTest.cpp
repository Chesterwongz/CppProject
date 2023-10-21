#include <memory>
#include <vector>
#include <catch.hpp>

#include "PQLParserTestUtils.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"

TEST_CASE("Valid Select BOOLEAN") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "b"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "c"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, BOOLEAN_KEYWORD)};

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);
}

TEST_CASE("Valid Select BOOLEAN - BOOLEAN as synonym") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, BOOLEAN_KEYWORD),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "b"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "c"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, BOOLEAN_KEYWORD)};

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query obj
  Query expected(dummyQpsParserPkbReader);

  vector<unique_ptr<SynonymArg>> synonymsToQuery = {};
  synonymsToQuery.push_back(
      std::make_unique<SynonymArg>(BOOLEAN_KEYWORD, ASSIGN_ENTITY));
  expected.setSynonymToQuery(std::move(synonymsToQuery));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Invalid Select<BOOLEAN, b, c>") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "b"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "c"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_LEFT_ANGLE_TOKEN, "<"),
                                PQLToken(PQL_NAME_TOKEN, BOOLEAN_KEYWORD),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "b"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "c"),
                                PQLToken(PQL_RIGHT_ANGLE_TOKEN, ">")};

  REQUIRE_THROWS_MATCHES(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPSSemanticError, Catch::Message("Using undeclared synonym: BOOLEAN"));
}

TEST_CASE("Valid Select BOOLEAN - no declarations") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, BOOLEAN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, "1"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_INTEGER_TOKEN, "2"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query obj
  Query expected(dummyQpsParserPkbReader);
  expected.setSynonymToQuery({});
  unique_ptr<Integer> firstArg = std::make_unique<Integer>("1");
  unique_ptr<Integer> secondArg = std::make_unique<Integer>("2");
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Select a.stmt#") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "b"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "c"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_PERIOD_TOKEN, "."),
                                PQLToken(PQL_NAME_TOKEN, ATTR_REF_STMT_NUMBER)};

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query obj
  Query expected(dummyQpsParserPkbReader);

  vector<unique_ptr<SynonymArg>> synonymsToQuery = {};
  synonymsToQuery.push_back(
      std::make_unique<SynonymArg>("a", ASSIGN_ENTITY, ATTR_REF_STMT_NUMBER));
  expected.setSynonymToQuery(std::move(synonymsToQuery));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Invalid Select a. - incomplete declaration") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "b"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "c"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_PERIOD_TOKEN, ".")};

  REQUIRE_THROWS_MATCHES(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPSSyntaxError,
      Catch::Message("Error occurred during tokenization, invalid token: "));
}

TEST_CASE("Invalid Select a.procName - incompatible attrRef") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "b"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "c"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_PERIOD_TOKEN, "."),
                                PQLToken(PQL_NAME_TOKEN, ATTR_REF_PROC_NAME)};

  REQUIRE_THROWS_MATCHES(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPSSemanticError, Catch::Message(QPS_SEMANTIC_ERR_INVALID_ATTR_REF));
}

TEST_CASE("Invalid Select a.asjdfjd - not an attrRef") {
  string notAttrRef = "myAss";
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "b"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "c"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_PERIOD_TOKEN, "."),
                                PQLToken(PQL_NAME_TOKEN, notAttrRef)};

  REQUIRE_THROWS_MATCHES(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPSSyntaxError, Catch::Message("AttrRef is invalid: myAss"));
}
