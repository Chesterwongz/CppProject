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

string followsSource =
    "procedure Follows {\n"
    "  read line1;\n"
    "  if (line2 > line2)then {\n"
    "  while((line3 < line3)&& ( line3 == line3)){\n"
    "    print line4;\n"
    "  }\n"
    "  } else {\n"
    "    assign = line5;\n"
    "  }\n"
    "  assign = line6;\n"
    "}";

TEST_CASE("SP-PKB-QPS Single Clause Follows - 1") {
    string query =
        "stmt Follows;\n"
        "Select Follows such that Follows (_,_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "2", "3", "4", "5", "6"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 2") {
    string query =
        "stmt stmt;\n"
        "Select stmt such that Follows (stmt ,_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "2"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 3") {
    string query =
        "stmt Select;\n"
        "Select Select such that Follows (_,Select)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"2", "6"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 4") {
    string query =
        "stmt s, S;\n"
        "Select s such that Follows (s,s)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    REQUIRE(result.empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 5") {
    string query =
        "stmt s, S;\n"
        "Select s such that Follows (s,S)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "2"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 6") {
    string query =
        "if Follows;\n"
        "Select Follows such that Follows   ( 1,Follows )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"2"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 7") {
    string query =
        "if Follows;\n"
        "Select Follows such that Follows   ( if,6 )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"2"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 8") {
    string query =
        "procedure p;\n"
        "Select p such that Follows   ( 2,6 )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"Follows"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 9") {
    string query =
        "stmt s;\n"
        "Select s such that Follows   ( 2,_ )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "2", "3", "4", "5", "6"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 10") {
    string query =
        "stmt s;\n"
        "Select s such that Follows   ( 3,_ ) ";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    REQUIRE(result.empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 11") {
    string query =
        "stmt s;\n"
        "Select s such that Follows   ( _,4 )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    REQUIRE(result.empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 12") {
    string query =
        "print p;\n"
        "Select p such that Follows( _,p)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    REQUIRE(result.empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 13") {
    string query =
        "print pn;\n"
        "Select pn such that Follows ( pn,_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    REQUIRE(result.empty());
}

TEST_CASE("SP-PKB-QPS Single Clause Follows - 14") {
    string query =
        "stmt s;assign a;\n"
        "Select a such that Follows( s,a )";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(followsSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"6"};
    REQUIRE(result == expected);
}
