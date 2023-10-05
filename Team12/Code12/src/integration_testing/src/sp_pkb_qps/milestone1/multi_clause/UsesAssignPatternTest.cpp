#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "pkb/facade/PKB.h"
#include "qps/QPS.h"
#include "sp/SourceProcessor.h"

using std::string, std::unordered_map, std::map, std::unordered_set, std::set,
    std::vector, std::pair;

// string usesAssignSource =
//     "procedure computeCentroid {\n"
//     "  count = 0;\n"
//     "  cenX = 0;\n"
//     "  cenY = 0;\n"
//     "  call readPoint;\n"
//     "  while ((x != 0) && ((y != 0)) {\n"
//     "    count = count + 1;\n"
//     "    cenX = cenX + x;\n"
//     "    cenY = cenY + y;\n"
//     "    call readPoint;\n"
//     "  }\n"
//     "  if (count == 0) then {\n"
//     "    flag = 1;\n"
//     "  } else {\n"
//     "    cenX = cenX / count;\n"
//     "    cenY = cenY / count;\n"
//     "  }\n"
//     "  normSq = cenX * cenX + cenY * cenY;\n"
//     "}";
//
// TEST_CASE("SP-PKB-QPS Uses Assign Pattern - 1") {
//     string query =
//         "read read;\n"
//         "Select read";
//     SourceProcessor sp;
//     PKB pkb;
//     sp.processContent(usesAssignSource, pkb.getWriter());
//     QPS qps(pkb.getReader());
//     auto result = qps.processQueryString(query);
//     set<string> expected = {"1", "7", "11", "12"};
//     REQUIRE(result == expected);
// }
