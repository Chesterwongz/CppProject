#include <memory>
#include <vector>
#include <catch.hpp>

#include "PQLParserTestUtils.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"
#include "qps/clause/clauseDecorator/notDecorator/NotDecorator.h"

TEST_CASE("Valid Uses(SYNONYM, SYNONYM)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> firstArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  unique_ptr<SynonymArg> secondArg =
      std::make_unique<SynonymArg>(d2, VARIABLE_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Uses(SYNONYM, _)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> firstArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Uses(SYNONYM, LITERAL_REF)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> firstArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("x");
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Uses(INTEGER, SYNONYM)") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "4";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, int1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Integer> firstArg = std::make_unique<Integer>(int1);
  unique_ptr<SynonymArg> secondArg =
      std::make_unique<SynonymArg>(d2, VARIABLE_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Uses(INTEGER, _)") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "4";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, int1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Integer> firstArg = std::make_unique<Integer>(int1);
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Uses(INTEGER, LITERAL_REF)") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "4";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, int1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Integer> firstArg = std::make_unique<Integer>(int1);
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("x");
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Uses(LITERAL_REF, SYNONYM)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Ident> firstArg = std::make_unique<Ident>("x");
  unique_ptr<SynonymArg> secondArg =
      std::make_unique<SynonymArg>(d2, VARIABLE_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Uses(LITERAL_REF, _)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Ident> firstArg = std::make_unique<Ident>("x");
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Uses(LITERAL_REF, LITERAL_REF)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "y"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Ident> firstArg = std::make_unique<Ident>("y");
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("x");
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Invalid Uses(LITERAL_EXPR, LITERAL_REF)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_EXPRESSION_TOKEN, "2"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_MATCHES(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPSSyntaxError,
      Catch::Message("Error occurred during tokenization, invalid token: 2"));
}

TEST_CASE("Invalid Uses(_, SYNONYM) - Wildcard cannot be first arg") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_AS(parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
                    QPSSemanticError);
}

TEST_CASE("Invalid Uses(INTEGER, SYNONYM) - invalid synonym type") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "4";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, int1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_AS(parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
                    QPSSemanticError);
}

TEST_CASE("Invalid Modifies(SYNONYM, SYNONYM) - both var arg") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "4";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, MODIFIES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_AS(parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
                    QPSSemanticError);
}

TEST_CASE("Invalid Modifies(SYNONYM, SYNONYM) - first const arg") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "4";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, CONSTANT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_AS(parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
                    QPSSemanticError);
}

TEST_CASE("Valid Modifies(INTEGER, SYNONYM)") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, MODIFIES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, "6"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>("v", VARIABLE_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Integer> firstArg = std::make_unique<Integer>("6");
  unique_ptr<SynonymArg> secondArg =
      std::make_unique<SynonymArg>("v", VARIABLE_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      MODIFIES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid not Uses(SYNONYM, SYNONYM)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> firstArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  unique_ptr<SynonymArg> secondArg =
      std::make_unique<SynonymArg>(d2, VARIABLE_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  unique_ptr<NotDecorator> notSuchThatClause =
      std::make_unique<NotDecorator>(std::move(suchThatClause));

  expected.addClause(std::move(notSuchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}
