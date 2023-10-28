#include <memory>
#include <vector>
#include <catch.hpp>

#include "PQLParserTestUtils.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/AssignPatternClause.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"
#include "qps/clause/clauseDecorator/notDecorator/NotDecorator.h"

TEST_CASE("Valid Pattern a (LITERAL_REF, PARTIAL_MATCH)") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "cenX"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>("newa", ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> outerSynonym =
      std::make_unique<SynonymArg>("newa", ASSIGN_ENTITY);
  unique_ptr<Ident> firstArg = std::make_unique<Ident>("cenX");
  unique_ptr<PatternExp> secondArg = std::make_unique<PatternExp>("x");
  vector<unique_ptr<AbstractArgument>> patternArg;
  patternArg.push_back(std::move(firstArg));
  patternArg.push_back(std::move(secondArg));
  unique_ptr<AssignPatternClause> patternClause =
      std::make_unique<AssignPatternClause>(std::move(outerSynonym),
                                            std::move(patternArg[0]),
                                            std::move(patternArg[1]), true);
  expected.addClause(std::move(patternClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Pattern a (LITERAL_REF, PARTIAL_EXPR_MATCH)") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "cenX"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_EXPRESSION_TOKEN, "x4 + y"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>("newa", ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> outerSynonym =
      std::make_unique<SynonymArg>("newa", ASSIGN_ENTITY);
  unique_ptr<Ident> firstArg = std::make_unique<Ident>("cenX");
  unique_ptr<PatternExp> secondArg = std::make_unique<PatternExp>("x4 + y");
  vector<unique_ptr<AbstractArgument>> patternArg;
  patternArg.push_back(std::move(firstArg));
  patternArg.push_back(std::move(secondArg));
  unique_ptr<AssignPatternClause> patternClause =
      std::make_unique<AssignPatternClause>(std::move(outerSynonym),
                                            std::move(patternArg[0]),
                                            std::move(patternArg[1]), true);
  expected.addClause(std::move(patternClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Pattern a (SYNONYM, PARTIAL_MATCH)") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(a1, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> outerSynonym =
      std::make_unique<SynonymArg>(a1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> firstArg =
      std::make_unique<SynonymArg>(var1, VARIABLE_ENTITY);
  unique_ptr<PatternExp> secondArg = std::make_unique<PatternExp>("x");
  vector<unique_ptr<AbstractArgument>> patternArg;
  patternArg.push_back(std::move(firstArg));
  patternArg.push_back(std::move(secondArg));
  unique_ptr<AssignPatternClause> patternClause =
      std::make_unique<AssignPatternClause>(std::move(outerSynonym),
                                            std::move(patternArg[0]),
                                            std::move(patternArg[1]), true);
  expected.addClause(std::move(patternClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Pattern a (_, PARTIAL_MATCH)") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(a1, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> outerSynonym =
      std::make_unique<SynonymArg>(a1, ASSIGN_ENTITY);
  unique_ptr<Wildcard> firstArg = std::make_unique<Wildcard>();
  unique_ptr<PatternExp> secondArg = std::make_unique<PatternExp>("x");
  vector<unique_ptr<AbstractArgument>> patternArg;
  patternArg.push_back(std::move(firstArg));
  patternArg.push_back(std::move(secondArg));
  unique_ptr<AssignPatternClause> patternClause =
      std::make_unique<AssignPatternClause>(std::move(outerSynonym),
                                            std::move(patternArg[0]),
                                            std::move(patternArg[1]), true);
  expected.addClause(std::move(patternClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Pattern a (SYNONYM, EXACT_MATCH)") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(a1, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> outerSynonym =
      std::make_unique<SynonymArg>(a1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> firstArg =
      std::make_unique<SynonymArg>(var1, VARIABLE_ENTITY);
  unique_ptr<PatternExp> secondArg = std::make_unique<PatternExp>("x");
  vector<unique_ptr<AbstractArgument>> patternArg;
  patternArg.push_back(std::move(firstArg));
  patternArg.push_back(std::move(secondArg));
  unique_ptr<AssignPatternClause> patternClause =
      std::make_unique<AssignPatternClause>(std::move(outerSynonym),
                                            std::move(patternArg[0]),
                                            std::move(patternArg[1]), false);
  expected.addClause(std::move(patternClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Invalid Pattern a (SYNONYM, LEFT_PARTIAL_MATCH)") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_WITH(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH);
}

TEST_CASE("Invalid Pattern a (LITERAL_REF, RIGHT_PARTIAL_MATCH)") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "cenX"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_WITH(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      "Error occurred during tokenization, invalid token: _");
}

TEST_CASE("Invalid Pattern a (SYNONYM, PARTIAL_MATCH) - non variable synonym") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, READ_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_AS(parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
                    QPSSemanticError);
}

TEST_CASE(
    "Invalid Pattern a (_LITERAL_REF_, PARTIAL_MATCH) - invalid 1st arg") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, READ_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_MATCHES(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPSSyntaxError,
      Catch::Message("Error occurred during tokenization, invalid token: x"));
}

TEST_CASE("Invalid Pattern a (LITERAL_REF_, PARTIAL_MATCH) - invalid 1st arg") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, READ_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_MATCHES(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPSSyntaxError,
      Catch::Message("Error occurred during tokenization, invalid token: _"));
}

TEST_CASE("Invalid Pattern a (SYNONYM, EXACT_EXPR_MATCH) - invalid expr") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_EXPRESSION_TOKEN, "+ x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_MATCHES(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPSSyntaxError, Catch::Message(QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH));
}

TEST_CASE(
    "Invalid Pattern a (SYNONYM, EXACT_EXPR_MATCH) "
    "- invalid expr, unmatched brackets") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_EXPRESSION_TOKEN, "5 + (x + y"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_MATCHES(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPSSyntaxError, Catch::Message(QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH));
}

TEST_CASE("Invalid Pattern a (SYNONYM, - incomplete query") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, a1),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, var1),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, a1),
                                PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, a1),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_NAME_TOKEN, var1),
                                PQLToken(PQL_COMMA_TOKEN, ",")};

  REQUIRE_THROWS_MATCHES(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPSSyntaxError, Catch::Message(QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY));
}

TEST_CASE("Valid Pattern not a (_, PARTIAL_MATCH)") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(a1, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> outerSynonym =
      std::make_unique<SynonymArg>(a1, ASSIGN_ENTITY);
  unique_ptr<Wildcard> firstArg = std::make_unique<Wildcard>();
  unique_ptr<PatternExp> secondArg = std::make_unique<PatternExp>("x");
  unique_ptr<AssignPatternClause> patternClause =
      std::make_unique<AssignPatternClause>(std::move(outerSynonym),
                                            std::move(firstArg),
                                            std::move(secondArg), true);
  unique_ptr<NotDecorator> notPatternClause =
      std::make_unique<NotDecorator>(std::move(patternClause));

  expected.addClause(std::move(notPatternClause));

  bool res = *query == expected;
  REQUIRE(res);
}
