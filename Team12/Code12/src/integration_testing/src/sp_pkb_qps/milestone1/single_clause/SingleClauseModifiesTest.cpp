// #include <catch.hpp>
// #include "sp/SourceProcessor.h"
// #include "pkb/facade/PKB.h"
// #include "qps/QPS.h"
// 
// #include <string>
// #include <unordered_map>
// #include <unordered_set>
// #include <vector>
// #include <map>
// #include <set>
//
// using std::string, std::unordered_map,std::map, std::unordered_set, std::set,
// std::vector, std::pair;
//
// string modifiesSource = "";
//
// TEST_CASE("SP-PKB-QPS Single Clause Modifies - 1") {
//    string query =
//        "read read;\n"
//        "Select read";
//    SourceProcessor sp;
//    PKB pkb;
//    sp.processContent(modifiesSource, pkb.getWriter());
//    QPS qps(pkb.getReader());
//    auto result = qps.processQueryString(query);
//    set<string> expected = {};
//    REQUIRE(result == expected);
// }
