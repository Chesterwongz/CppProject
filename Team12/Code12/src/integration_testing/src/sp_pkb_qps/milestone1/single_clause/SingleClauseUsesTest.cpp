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

string usesSource =
    "procedure procedure {  read read;\n"
    "  print print;\n"
    "  while ((!(while != while))||(while<=while)) {\n"
    "    if ((if == if) && ( ! (if >= if))) then{\n"
    "        assign = variable + 5;\n"
    "        if ((if2 < if2) && ( ! (if2 > if2))) then{\n"
    "                read read2;\n"
    "                print print2;\n"
    "                while ((while2 > while2)&&(!(while2<while2))) {\n"
    "                    assign2 = variable2 + 10;\n"
    "                }} else {read read3;\n"
    "             }        }else{read read4;}}}";

TEST_CASE("SP-PKB-QPS integration - 1") {
    string query =
        "read read;\n"
        "Select read";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(usesSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "7", "11", "12"};
    REQUIRE(result == expected);
}