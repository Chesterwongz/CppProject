#include <catch.hpp>

#include "../PQLParserTestUtils.h"
#include "qps/clause/patternClause/AssignPatternClause.h"

TEST_CASE("Component invalid with IDENT = INTEGER") {
  string query = "Select BOOLEAN with 2 = \"x\"";

  REQUIRE_THROWS_AS(parseStringToQuery(query),
                    QPSSemanticError);
}

TEST_CASE("Valid attrRef = INTEGER") {
  string query = "assign newa; Select BOOLEAN with newa.stmt#=2";

  parseStringToQuery(query);
}

TEST_CASE("Valid Select <r, r.varName, r.stmt#>") {
  string query =
      "read r;\n"
      "Select <r, r.varName, r.stmt#> with r.varName = \"d\" and r.stmt# = 5 "
      "and r.varName = \"d\"";

  parseStringToQuery(query);
}
