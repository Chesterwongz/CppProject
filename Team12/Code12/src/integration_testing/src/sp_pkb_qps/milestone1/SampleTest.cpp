#include "catch.hpp"
#include "sp/SourceProcessor.h"
#include "pkb/facade/PKB.h"
#include "qps/QPS.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <set>

using std::string, std::unordered_map,std::map, std::unordered_set, std::set, std::vector, std::pair;
        
string sampleSource = 
    "procedure Example {"
    "  x = 2;"
    "  z = 3;"
    "  i = 5;"
    "  while (i!=0) {"
    "    x = x - 1;"
    "    if (x==1) then {"
    "      z = x + 1; }"
    "    else {"
    "      y = z + x; }"
    "    z = z + x + i;"
    "    call q;"
    "    i = i - 1; }"
    "  call p; }"
    ""
    "procedure p {"
    "  if (x<0) then {"
    "    while (i>0) {"
    "      x = z * 3 + 2 * y;"
    "      call q;"
    "      i = i - 1; }"
    "    x = x + 1;"
    "    z = x + z; }"
    "  else {"
    "    z = 1; }"
    "  z = z + x + i; }"
    ""
    "procedure q {"
    "  if (x==1) then {"
    "    z = x + 1; }"
    "  else {"
    "    x = z + x; } }";

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 1") {
    string query =
        "while w;\n"
        "Select w such that Parent(w, 7)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 2") {
    string query =
        "if ifs;\n"
        "Select ifs such that Follows(5, ifs)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"6"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 3") {
    string query =
        "assign a;\n"
        "Select a such that Parent*(4, a)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"5", "7", "8", "9", "11"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 4") {
    string query =
        "call c;\n"
        "Select c such that Follows*(1, c)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"12"};
    REQUIRE(result == expected);
}
