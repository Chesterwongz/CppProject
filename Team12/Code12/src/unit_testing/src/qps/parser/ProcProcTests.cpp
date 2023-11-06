#include <memory>
#include <vector>
#include <catch.hpp>

#include "PQLParserTestUtils.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"

TEST_CASE("Valid Calls(SYNONYM, SYNONYM)") {
  string p1 = "proc";
  string p2 = "procedure";
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, PROCEDURE_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, p1),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, p2),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, p1),
                                PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_NAME_TOKEN, p1),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, p2),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};

  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(p1, PROCEDURE_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> firstArg =
      std::make_unique<SynonymArg>(p1, PROCEDURE_ENTITY);
  unique_ptr<SynonymArg> secondArg =
      std::make_unique<SynonymArg>(p2, PROCEDURE_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      CALLS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Calls(SYNONYM, _)") {
  string p1 = "proc";
  string p2 = "procedure";
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, PROCEDURE_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, p1),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, p2),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, p1),
                                PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_NAME_TOKEN, p1),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};

  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(p1, PROCEDURE_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> firstArg =
      std::make_unique<SynonymArg>(p1, PROCEDURE_ENTITY);
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      CALLS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Calls(SYNONYM, LITERAL_REF)") {
  string p1 = "hello";
  string p2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, PROCEDURE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, p1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, p2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, p1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, p1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "potato"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(p1, PROCEDURE_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> firstArg =
      std::make_unique<SynonymArg>(p1, PROCEDURE_ENTITY);
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("potato");
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      CALLS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Calls(_, SYNONYM)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, PROCEDURE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, PROCEDURE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, PROCEDURE_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Wildcard> firstArg = std::make_unique<Wildcard>();
  unique_ptr<SynonymArg> secondArg =
      std::make_unique<SynonymArg>(d2, PROCEDURE_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      CALLS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Calls(_, _)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, PROCEDURE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, PROCEDURE_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Wildcard> firstArg = std::make_unique<Wildcard>();
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      CALLS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Calls(_, LITERAL_REF)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "potato"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, PROCEDURE_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Wildcard> firstArg = std::make_unique<Wildcard>();
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("potato");
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      CALLS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Calls(LITERAL_REF, SYNONYM)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, PROCEDURE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "literal"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Ident> firstArg = std::make_unique<Ident>("literal");
  unique_ptr<SynonymArg> secondArg =
      std::make_unique<SynonymArg>(d2, PROCEDURE_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      CALLS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Calls(LITERAL_REF, _)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "literal"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Ident> firstArg = std::make_unique<Ident>("literal");
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      CALLS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Calls(LITERAL_REF, LITERAL_REF)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "literal1"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "literal2"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Ident> firstArg = std::make_unique<Ident>("literal1");
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("literal2");
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      CALLS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Calls*(LITERAL_REF, LITERAL_REF)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_STAR_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "literal1"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "literal2"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(d1, STMT_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Ident> firstArg = std::make_unique<Ident>("literal1");
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("literal2");
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      CALLS_STAR_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Calls(SYNONYM, _) - keyword as synonym") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, PROCEDURE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(CALLS_ABSTRACTION, PROCEDURE_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> firstArg =
      std::make_unique<SynonymArg>(CALLS_ABSTRACTION, PROCEDURE_ENTITY);
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      CALLS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Invalid Calls(SYNONYM, SYNONYM) - both are not proc synonyms") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, WHILE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_AS(parseToQuery(tokenList),
                    QPSSemanticError);
}

TEST_CASE("Invalid Calls clause - undeclared synonym") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, "a"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_AS(parseToQuery(tokenList),
                    QPSSemanticError);
}

TEST_CASE("Invalid Calls clause - invalid LITERAL_EXP_TOKEN") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_EXPRESSION_TOKEN, "1"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  REQUIRE_THROWS_MATCHES(
      parseToQuery(tokenList),
      QPSSyntaxError,
      Catch::Message("Error occurred during tokenization, invalid token: 1"));
}

TEST_CASE("Invalid Calls clause - only 1 argument") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, CALLS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  REQUIRE_THROWS_MATCHES(
      parseToQuery(tokenList),
      QPSSyntaxError, Catch::Message(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT));
}
