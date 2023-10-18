#include <memory>
#include <string>
#include <vector>
#include <catch.hpp>

#include "../PQLParserTestUtils.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"

TEST_CASE("Component invalid with IDENT = INTEGER") {
  string query = "Select BOOLEAN with 2 = \"x\"";

  REQUIRE_THROWS_MATCHES(parseStringToQuery(query, dummyQpsParserPkbReader),
                         QPSSemanticError,
                         Catch::Message(QPS_SEMANTIC_ERR_INVALID_WITH));
}

TEST_CASE("Valid attrRef = INTEGER") {
  string query = "assign newa; Select BOOLEAN with newa.stmt#=2";

  parseStringToQuery(query, dummyQpsParserPkbReader);
}
