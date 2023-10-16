#include <memory>
#include <vector>
#include <catch.hpp>

#include "PQLParserTestUtils.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"

TEST_CASE("Valid Select<a,b,c>") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "b"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "c"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_LEFT_ANGLE_TOKEN, "<"),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "b"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_NAME_TOKEN, "c"),
                                PQLToken(PQL_RIGHT_ANGLE_TOKEN, ">")};

  std::unique_ptr<Query> query =
      parseToQuery(std::move(tokenList), dummyQpsParserPkbReader);
}
