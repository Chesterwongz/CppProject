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

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 5") {
    string query =
        "stmt s;\n"
        "Select s such that Modifies(s, \"i\")";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"3", "4", "11", "12", "13", "14", "17"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 6") {
    string query =
        "variable v;\n"
        "Select v such that Uses(\"p\", v)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"i", "x", "y", "z"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 7") {
    string query =
        "procedure p;\n"
        "Select p such that Calls(p, \"q\")";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"Example", "p"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 8") {
    string query =
        "procedure p;\n"
        "Select p such that Calls*(\"Example\", p)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"p", "q"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 9") {
    string query =
        "prog_line n;\n"
        "Select n such that Next(4, n)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"5", "12"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 10") {
    string query =
        "prog_line n;\n"
        "Select n such that Next*(n, 4)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 11") {
    string query =
        "assign a;\n"
        "Select a such that Affects(a, 9)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"2", "3", "5", "7", "11"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 12") {
    string query =
        "assign a;\n"
        "Select a such that Affects*(11, a)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"9", "11"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 13") {
    string query =
        "assign a;\n"
        "Select a pattern a(\"z\", _\"x+i\")";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 14") {
    string query =
        "assign a;\n"
        "Select a pattern a(_, _\"x + 1\"_)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"7", "18", "23"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 15") {
    string query =
        "assign a;\n"
        "Select a pattern a(_, \" 3  +  2 \")";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 16") {
    string query =
        "while w; variable v;\n"
        "Select w such that Modifies(w, v) with v.varName = \"x\"";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"4", "14"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 17") {
    string query =
        "if ifs; variable v;\n"
        "Select v such that Uses(ifs, v) with ifs.stmt# = 22";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"x", "z"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 18") {
    string query =
        "procedure p, q;\n"
        "Select BOOLEAN such that Calls(p, q) with q.procName = \"p\" and p.procName = \"Example\"";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"TRUE"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 19") {
    string query =
        "if ifs; assign a1, a2; variable v1, v2;\n"
        "Select ifs such that Follows*(a1, ifs) and Follows*(ifs, a2) and Modifies(ifs, v1) and Uses(ifs, v2) with v1.varName = v2.varName";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"6"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 20") {
    string query =
        "prog_line n; stmt s;\n"
        "Select s such that Next*(16, n) and Parent*(s, n)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"13", "14"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 21") {
    string query =
        "prog_line n; assign a;\n"
        "Select a such that Affects*(a, n) and Next*(13, n)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"17", "18", "19", "20"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 22") {
    string query =
        "procedure p, q; variable v;\n"
        "Select <p, q, v> such that Modifies(p, v) and Calls(p, q)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"Example p i", "Example p x", "Example p y", "Example p z", "Example q i", "Example q x", "Example q y", "Example q z", "p q i", "p q x", "p q z"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 23") {
    string query =
        "call c; assign a1, a2;\n"
        "Select BOOLEAN such that Follows*(_, c) and Affects(a1, a2) and Uses(a2, _)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"TRUE"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 24") {
    string query =
        "assign a1, a2; variable v;\n"
        "Select v pattern a1(v, _) such that Affects*(a1, a2) and Uses(a2, v)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"i", "x", "z"};
    REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 25") {
    string query =
        "prog_line n1, n2; variable v; call c;\n"
        "Select c such that Next*(n1, n2) and Modifies(n1, v) and Uses(n2, v) and Modifies(c, v)";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(sampleSource, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {"10", "12", "16"};
    REQUIRE(result == expected);
}
