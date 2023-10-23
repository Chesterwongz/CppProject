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

string whileSource =
    "procedure p {"
    "while (1 == 2) {"     // 1
    "while (hoho == 4) {"  // 2
    "x = 1;"               // 3
    "}"
    "}"
    "while (x == 5) {"         // 4
    "if (huehue == 1) then {"  // 5
    "while (hehe == x) {"      // 6
    "z = 2;"                   // 7
    "}"
    "}"
    "else {"
    "y = 3;"  // 8
    "}"
    "}"
    "while (oi == 11) {"  // 9
    "oi = oi + 1;"        // 10
    "}"
    "while (9 == 11) {"  // 11
    "while (oi == 2) {"  // 12
    "oi = oi - 1;"       // 13
    "while (2 == oi) {"  // 14
    "oi = oi - 2;"       // 15
    "}"
    "}"
    "}"
    "}";

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/whilePattern_queries.txt - "
    "1") {
  // wildcard first arg - return all while statments that use a variable
  string query =
      "while while;\n"
      "Select while pattern while(_, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(whileSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2", "4", "6", "9", "12", "14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/whilePattern_queries.txt - "
    "2") {
  // wildcard first arg, but select different while - return all while statments
  string query =
      "while w1, w2;\n"
      "Select w1 pattern w2(_, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(whileSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "2", "4", "6", "9", "11", "12", "14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/whilePattern_queries.txt - "
    "3") {
  // synonym first arg - return all while statements that use a variable
  string query =
      "while w; variable v;\n"
      "Select w pattern w(v, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(whileSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2", "4", "6", "9", "12", "14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/whilePattern_queries.txt - "
    "4") {
  // synonym first arg, but select different while - return all while statments
  string query =
      "while w1, w2; variable d;\n"
      "Select w1 pattern w2(d, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(whileSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "2", "4", "6", "9", "11", "12", "14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/whilePattern_queries.txt - "
    "5") {
  // ident first arg - return all while statements that use specific ident
  string query =
      "while w;\n"
      "Select w pattern w(\"oi\", _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(whileSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"9", "12", "14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/whilePattern_queries.txt - "
    "6") {
  // ident first arg, but select different while - return all if statments
  // since a while statement that uses "hoho" exists
  string query =
      "while w1, w2;\n"
      "Select w1 pattern w2(\"hoho\", _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(whileSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "2", "4", "6", "9", "11", "12", "14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/whilePattern_queries.txt - "
    "7") {
  // ident first arg, but select different while - return none
  // since a while statement that uses "huehue" DOES NOT exist
  string query =
      "while w1, w2;\n"
      "Select w1 pattern w2(\"huehue\", _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(whileSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

string whileSource2 =
    "procedure test {\n"
    "  a = 1;\n"
    "  print b;\n"
    "  read c;\n"
    "  if (x == 2) then {\n"
    "    a = 2;\n"
    "  } else {\n"
    "    c = 3;\n"
    "  }\n"
    "  while (x == 2) {\n"
    "    d = 4;\n"
    "  }\n"
    "}";

// TODO(Hwee): Rename this test
TEST_CASE("SP-PKB-QPS we shall rename this later") {
  string query =
      "stmt s1, s2; assign a1, a2; print p1, p2; read r1, r2; if i1, i2; while "
      "w1, w2; call cl1, cl2; procedure pr1, pr2; constant c1, c2; variable "
      "v1, v2;\n"
      "Select s1 pattern w1(v1, \"1\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(whileSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}
