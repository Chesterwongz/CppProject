#include <memory>
#include <vector>
#include <catch.hpp>

#include "PQLParserTestUtils.h"
#include "pkb/facade/PKBReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/AssignPatternClause.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"

using std::unique_ptr, std::make_unique, std::move, std::vector;

TEST_CASE("Invalid parser state - declarative") {
  const string name = "akfsdjfhs";
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, name)};

  PKBStorage storage{};
  PKBReader pkbReader(storage);

  REQUIRE_THROWS_WITH(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPS_TOKENIZATION_ERR + name);
}

TEST_CASE("incomplete query - only declarative clause") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "a"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
  };

  REQUIRE_THROWS_WITH(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPS_TOKENIZATION_ERR_INCOMPLETE_DECLARATION);
}

TEST_CASE("invalid query - select undeclared synonym") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "a"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "a1"),
  };

  REQUIRE_THROWS_WITH(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      "Using undeclared synonym: a1");
}

TEST_CASE("valid simple transitive follows") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "a"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "a"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_STAR_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, "5"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>("a", ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<Integer> firstArg = std::make_unique<Integer>("5");
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
      FOLLOWS_STAR_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("valid simple uses") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, "14"),
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

  unique_ptr<Integer> firstArg = std::make_unique<Integer>("14");
  unique_ptr<SynonymArg> secondArg =
      std::make_unique<SynonymArg>("v", VARIABLE_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("valid such that before pattern") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, "assign"),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, "Select"),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_NAME_TOKEN, "such"),
                                PQLToken(PQL_NAME_TOKEN, "that"),
                                PQLToken(PQL_NAME_TOKEN, "Uses"),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
                                PQLToken(PQL_NAME_TOKEN, "pattern"),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>("a", ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> firstSuchThatArg =
      std::make_unique<SynonymArg>("a", ASSIGN_ENTITY);
  unique_ptr<Ident> secondSuchThatArg = std::make_unique<Ident>("x");
  unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstSuchThatArg), std::move(secondSuchThatArg));
  expected.addClause(std::move(suchThatClause));

  unique_ptr<SynonymArg> outerSynonym =
      std::make_unique<SynonymArg>("a", ASSIGN_ENTITY);
  unique_ptr<Ident> firstPatternArg = std::make_unique<Ident>("x");
  unique_ptr<Wildcard> secondPatternArg = std::make_unique<Wildcard>();
  vector<unique_ptr<AbstractArgument>> patternArg;
  patternArg.push_back(std::move(firstPatternArg));
  patternArg.push_back(std::move(secondPatternArg));
  unique_ptr<AssignPatternClause> patternClause =
      make_unique<AssignPatternClause>(std::move(outerSynonym),
                                       std::move(patternArg[0]),
                                       std::move(patternArg[1]), false);
  expected.addClause(std::move(patternClause));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("invalid query - Uses clause only has 1 argument") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
                                PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};

  REQUIRE_THROWS_WITH(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
}

TEST_CASE("invalid query - Pattern clause only has 1 argument") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
                                PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};

  REQUIRE_THROWS_WITH(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH);
}

TEST_CASE("valid pattern before such that") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
                                PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>("a", ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  unique_ptr<SynonymArg> outerSynonym =
      std::make_unique<SynonymArg>("a", ASSIGN_ENTITY);
  unique_ptr<Ident> firstPatternArg = std::make_unique<Ident>("x");
  unique_ptr<Wildcard> secondPatternArg = std::make_unique<Wildcard>();
  vector<unique_ptr<AbstractArgument>> patternArg;
  patternArg.push_back(std::move(firstPatternArg));
  patternArg.push_back(std::move(secondPatternArg));
  unique_ptr<AssignPatternClause> patternClause =
      make_unique<AssignPatternClause>(std::move(outerSynonym),
                                       std::move(patternArg[0]),
                                       std::move(patternArg[1]), false);
  expected.addClause(std::move(patternClause));

  unique_ptr<SynonymArg> firstSuchThatArg =
      std::make_unique<SynonymArg>("a", ASSIGN_ENTITY);
  unique_ptr<Ident> secondSuchThatArg = std::make_unique<Ident>("x");
  unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstSuchThatArg), std::move(secondSuchThatArg));
  expected.addClause(std::move(suchThatClause));

  bool res = *query == expected;
  REQUIRE(res);
}
