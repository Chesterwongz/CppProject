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

string assignSource =
    "procedure AssignPattern {\n"
    "  line1 = 1 + 2 + 3 + 4;\n"
    "  line2 = a + b -c * d /  e %f;\n"
    "  if ((line3 + 1) == (a + 1)) then {\n"
    "    line4 = 1;\n"
    "  } else {\n"
    "    line5 = a;\n"
    "    while ((((line6 )- 1) > (a - 1)) && (!(1 != 1))) {\n"
    "        line7 = a + 1;\n"
    "    }\n"
    "  }\n"
    "}";

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 1") {
    string query =
        "assign a;\n"
        "Select a pattern a(_, _\"1\"_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "4", "7"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 2") {
    string query =
        "assign a;\n"
        "Select a pattern a(_, _\"a\"_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"2", "5", "7"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 3") {
    string query =
        "assign a;\n"
        "Select a pattern a(_,_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "2", "4", "5", "7"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 4") {
    string query =
        "assign a;\n"
        "Select a pattern a(\"line1\", _\"1\"_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 5") {
    string query =
        "assign a;\n"
        "Select a pattern a(\"line2\", _\"a\"_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"2"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 6") {
    string query =
        "assign a;\n"
        "Select a pattern a(\"line4\",_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"4"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 7") {
    string query =
        "assign a;\n"
        "Select a pattern a(\"line1\", _\"12\"_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    REQUIRE(qps.processQueryString(query).empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 8") {
    string query =
        "assign a;\n"
        "Select a pattern a(\"line2\", _\"ab\"_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    REQUIRE(qps.processQueryString(query).empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 9") {
    string query =
        "assign a; variable v;\n"
        "Select a pattern a(\"v\",_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    REQUIRE(qps.processQueryString(query).empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 10") {
    string query =
        "assign a; variable v;\n"
        "Select v pattern a(v,_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    set<string> expected = {"line1", "line2", "line4", "line5", "line7"};
    REQUIRE(qps.processQueryString(query) == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 11") {
    string query =
        "assign a; variable v;\n"
        "Select v pattern a(v, _\"1\"_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());

    set<string> expected = {"line1", "line4", "line7"};
    REQUIRE(qps.processQueryString(query) == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Assign Pattern - 12") {
    string query =
        "assign a; variable v;\n"
        "Select v pattern a(v, _\"a\"_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(assignSource, pkb.getWriter());
    QPS qps(pkb.getReader());

    set<string> expected = {"line2", "line5", "line7"};
    REQUIRE(qps.processQueryString(query) == expected);
}
