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

string followsStarSource =
    "procedure FollowsT {\n"
    "  read line1;\n"
    "  if (line2 > line2)then {\n"
    "  while((line3 < line3)&& ( line3 == line3)){\n"
    "    print line4;\n"
    "    assign5 = line5;\n"
    "  }\n"
    "      read line6;\n"
    "  } else {\n"
    "    assign7 = line7;\n"
    "  }\n"
    "  assign8 = line8;\n"
    "}";

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 1") {
    string query =
        "stmt Follows;\n"
        "Select Follows such that Follows* (_,_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "2", "3", "4", "5", "6", "7", "8"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 2") {
    string query =
        "stmt stmt;\n"
        "Select stmt such that Follows *(stmt ,_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "2", "3", "4"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 3") {
    string query =
        "stmt Select;\n"
        "Select Select such that Follows*(_,Select)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"2", "5", "6", "8"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 4") {
    string query =
        "stmt s, S;\n"
        "Select s such that Follows *(s,s)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    REQUIRE(result.empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 5") {
    string query =
        "stmt s, S;\n"
        "Select s such that Follows *(s,S)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "2", "3", "4"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 6") {
    string query =
        "stmt Follows;\n"
        "Select Follows such that Follows *  ( 1,Follows )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"2", "8"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 7") {
    string query =
        "stmt if;\n"
        "Select if such that Follows  * ( if,5 )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"4"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 8") {
    string query =
        "procedure p;\n"
        "Select p such that Follows*   ( 3,6 )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"FollowsT"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 9") {
    string query =
        "stmt s;\n"
        "Select s such that Follows* (2,_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "2", "3", "4", "5", "6", "7", "8"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 10") {
    string query =
        "stmt s;\n"
        "Select s such that Follows*(5,_ )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    REQUIRE(result.empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 11") {
    string query =
        "stmt s;\n"
        "Select s such that Follows   *( _,4 )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    REQUIRE(result.empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 12") {
    string query =
        "print p;\n"
        "Select p such that Follows*( _,p)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    REQUIRE(result.empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 13") {
    string query =
        "print pn;\n"
        "Select pn such that Follows ( pn,_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"4"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows Star - 14") {
    string query =
        "stmt s;assign a;\n"
        "Select a such that Follows( s,a )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsStarSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"5", "8"};
    REQUIRE(result == expected);
}
