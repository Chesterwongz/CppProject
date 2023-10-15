#include <memory>
#include <string>
#include <vector>
#include <catch.hpp>

#include "PQLParserTestUtils.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/query/Query.h"
#include "qps/token/PQLToken.h"

TEST_CASE("Invalid with IDENT = INTEGER") {
  string ass1 = "newa";
  vector<PQLToken> tokenList = {PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, BOOLEAN_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, WITH_KEYWORD),
                                PQLToken(PQL_INTEGER_TOKEN, "2"),
                                PQLToken(PQL_EQUALS_TOKEN, "="),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x")};

  REQUIRE_THROWS_MATCHES(
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader),
      QPSSemanticError, Catch::Message(QPS_SEMANTIC_ERR_INVALID_WITH));
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
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);

  // expected query object
  Query expected(dummyQpsParserPkbReader);

  unique_ptr<SynonymArg> synonymArg =
      std::make_unique<SynonymArg>(ass1, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect = {};
  synonymsToSelect.emplace_back(std::move(synonymArg));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  // TODO(Hwee): add with test cases
}
