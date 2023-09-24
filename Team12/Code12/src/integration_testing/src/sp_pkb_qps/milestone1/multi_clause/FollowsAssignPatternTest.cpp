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

string followsAssignSource =
    "procedure FollowsPattern{\n"
    "  read line1;\n"
    "  if (line2 > line2)then {\n"
    "  while((line3 < line3)&& ( line3 == line3)){\n"
    "    print line4;\n"
    "    assign5 = line5 + line5;\n"
    "  }\n"
    "      read line6;\n"
    "  } else {\n"
    "    assign7 = (line7+line7)/line7*line7-line7%(line7);\n"
    "  }\n"
    "  assign8 = line8;\n"
    "}";

TEST_CASE("SP-PKB-QPS Follows Assign - 1") {
    string query =
        "read read;\n"
        "Select read";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsAssignSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "7", "11", "12"};
    REQUIRE(result == expected);
}