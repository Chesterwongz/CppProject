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

string parentStarSource =
    "procedure Parent {    read line1;\n"
    "    if (line2 > line2) then{\n"
    "        while((line3 <= line3)&& ( line3 == line3)){\n"
    "            read line4;\n"
    "            print line5;\n"
    "            if (line6 > line6) then{\n"
    "                if ((line7 * 7 == (line7 + 7)%7)||(! ( line7/line7 != line7/line7+7)))then{\n"
    "                  assign8 = line8;\n"
    "                  assign9 = line9 * 9 + (9) * (line9 / line9);\n"
    "                } else {\n"
    "                    while(line10 < line10){\n"
    "                        while((line11 < line11)&& ( line11 == line11)){\n"
    "                            print line12;\n"
    "                        }\n"
    "                    }\n"
    "                }\n"
    "            } else {\n"
    "                if (line13 > line13) then{\n"
    "                    while((line14) < (line14)){\n"
    "                      read line15;\n"
    "                    }\n"
    "                } else {\n"
    "                    assign16 = line16/16;\n"
    "                }\n"
    "            }\n"
    "        }\n"
    "    } else {\n"
    "        print line17;\n"
    "    }\n"
    "    assign18 = line18;\n"
    "}";

TEST_CASE("SP-PKB-QPS Single Clause Parent Star - 1") {
    string query =
        "read read;\n"
        "Select read";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(parentStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "7", "11", "12"};
    REQUIRE(result == expected);
}