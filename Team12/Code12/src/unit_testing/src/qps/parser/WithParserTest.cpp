#include <memory>
#include <string>
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

TEST_CASE("Invalid with IDENT = INTEGER") {
  vector<PQLToken> tokenList = {PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, BOOLEAN_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, WITH_KEYWORD),
                                PQLToken(PQL_INTEGER_TOKEN, "2"),
                                PQLToken(PQL_EQUALS_TOKEN, "="),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x")};

  REQUIRE_THROWS_AS(parseToQuery(tokenList),
                    QPSSemanticError);
}

TEST_CASE("Valid with attrRef = INTEGER") {
  string ass1 = "newa";
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, BOOLEAN_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, WITH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_PERIOD_TOKEN, "."),
                                PQLToken(PQL_NAME_TOKEN, ATTR_REF_STMT_NUMBER),
                                PQLToken(PQL_EQUALS_TOKEN, "="),
                                PQLToken(PQL_INTEGER_TOKEN, "2")};

  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(ass1, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  // TODO(Hwee): add with test cases
}

TEST_CASE("Valid with not attrRef = INTEGER") {
  string ass1 = "newa";
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_NAME_TOKEN, WITH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_PERIOD_TOKEN, "."),
                                PQLToken(PQL_NAME_TOKEN, ATTR_REF_STMT_NUMBER),
                                PQLToken(PQL_EQUALS_TOKEN, "="),
                                PQLToken(PQL_INTEGER_TOKEN, "5")};

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList));

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(ass1, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  // TODO(Hwee): add with test cases
}

TEST_CASE("Valid with not INTEGER = attrRef") {
  string ass1 = "newa";
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_NAME_TOKEN, WITH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
                                PQLToken(PQL_INTEGER_TOKEN, "5"),
                                PQLToken(PQL_EQUALS_TOKEN, "="),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_PERIOD_TOKEN, "."),
                                PQLToken(PQL_NAME_TOKEN, ATTR_REF_STMT_NUMBER)};

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList));

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(ass1, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  // TODO(Hwee): add with test cases
}

TEST_CASE("Valid with not LITERAL_REF = attrRef") {
  string ass1 = "newa";
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, PROCEDURE_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_NAME_TOKEN, WITH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "hello"),
                                PQLToken(PQL_EQUALS_TOKEN, "="),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_PERIOD_TOKEN, "."),
                                PQLToken(PQL_NAME_TOKEN, ATTR_REF_PROC_NAME)};

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList));

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(ass1, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  // TODO(Hwee): add with test cases
}

TEST_CASE("Valid with not LITERAL_REF = LITERAL_REF") {
  string ass1 = "newa";
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, PROCEDURE_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, ass1),
                                PQLToken(PQL_NAME_TOKEN, WITH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "hello"),
                                PQLToken(PQL_EQUALS_TOKEN, "="),
                                PQLToken(PQL_LITERAL_REF_TOKEN, ass1)};

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList));

  // expected query object
  Query expected{};

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(ass1, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  // TODO(Hwee): add with test cases
}
