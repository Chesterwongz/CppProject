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

string ms2AssignSource =
    "procedure AssignPattern {"
    "  line1 = 1 + 2 + 3 + 4;"
    "  line2 = a + b -c * d /  e %f;"
    "  if ((line3 + 1) == (a + 1)) then {"
    "    line4 = 1;"
    "  } else {"
    "    line5 = a;"
    "    while ((((line6 )- 1) > (a - 1)) && (!(1 != 1))) {"
    "        line7 = a + 1;"
    "        line8 = 2 + 3;"
    "    }"
    "  }"
    "}";

// partial matching tests with operator since ms1 no operator for partial match

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "1") {
  // wildcard first arg, partial match ident second arg (with operator)
  string query =
      "assign a;\n"
      "Select a pattern a(_, _\"1 + 2 + 3\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "2") {
  // wildcard first arg, partial match ident second arg version 2 - no results
  // (with operator)
  string query =
      "assign a;\n"
      "Select a pattern a(_, _\"2 + 3\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "3") {
  // ident first arg, partial match ident second arg (with operator)
  string query =
      "assign a;\n"
      "Select a pattern a(\"line2\", _\"c * d / e\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "4") {
  // ident first arg, partial match ident second arg version 2 - no results
  // (with operator)
  string query =
      "assign a;\n"
      "Select a pattern a(\"line1\", _\"d / e\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "5") {
  // synonym first arg, partial match ident second arg - select v (with
  // operator)
  string query =
      "assign a; variable v;\n"
      "Select v pattern a(v,_\"2 + 3\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"line8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "6") {
  // synonym first arg, partial match ident second arg - select a (with
  // operator)
  string query =
      "assign a; variable v;\n"
      "Select a pattern a(v,_\"2 + 3\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"8"};
  REQUIRE(result == expected);
}

// Exact matching tests
TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "7") {
  // wildcard first arg, exact match ident second arg (no operator)
  string query =
      "assign a;\n"
      "Select a pattern a(_, \"a\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"5"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "8") {
  // wildcard first arg, exact match ident second arg version 2 (with operator)
  string query =
      "assign a;\n"
      "Select a pattern a(_, \"a+b-c*d/e%f\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "9") {
  // wildcard first arg, exact match ident second arg version 3 - no results
  // (no operator)
  string query =
      "assign a;\n"
      "Select a pattern a(_, \"2\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "10") {
  // wildcard first arg, exact match ident second arg
  // select different assign
  // return all assign statements since pattern evals to true (no operator)
  string query =
      "assign a1, a2;\n"
      "Select a1 pattern a2(_, \"1\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "4", "5", "7", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "11") {
  // wildcard first arg, exact match ident second arg
  // select different assign
  // return none since pattern evals to false (with operator)
  string query =
      "assign a1, a2;\n"
      "Select a1 pattern a2(_, \"1 + 2 + 3 + 4 + 5 + 6\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "12") {
  // ident first arg, exact match ident second arg (with operator)
  string query =
      "assign a;\n"
      "Select a pattern a(\"line1\", \"1 + 2 + 3 + 4\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "13") {
  // ident first arg, exact match ident second arg version 2 (no operator)
  string query =
      "assign a;\n"
      "Select a pattern a(\"line4\", \"1\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"4"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "14") {
  // ident first arg, exact match ident second arg version 3 - no results
  // (with operator)
  string query =
      "assign a;\n"
      "Select a pattern a(\"line1\", \"12 + abc\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "15") {
  // ident first arg, exact match ident second arg version 4 - no results
  // (no operator)
  string query =
      "assign a;\n"
      "Select a pattern a(\"line2\", \"ab\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "16") {
  // ident first arg, exact match ident second arg (no operator)
  // select different assign
  // return all assign statements since pattern evals to true
  string query =
      "assign a1, a2;\n"
      "Select a1 pattern a2(\"line5\", \"a\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "4", "5", "7", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "17") {
  // ident first arg, exact match ident second arg (with operator)
  // select different assign
  // return none since pattern evals to false
  string query =
      "assign a1, a2;\n"
      "Select a1 pattern a2(\"line2\", \"a + a\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "18") {
  // synonym first arg, exact match ident second arg - select v (no operator)
  string query =
      "assign a; variable v;\n"
      "Select v pattern a(v,\"1\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"line4"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "19") {
  // synonym first arg, exact match ident second arg - select a (no operator)
  string query =
      "assign a; variable v;\n"
      "Select a pattern a(v,\"1\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"4"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "20") {
  // synonym first arg, exact match ident second arg - select v (with operator)
  string query =
      "assign a; variable v;\n"
      "Select v pattern a(v,\"a + 1\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"line7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "21") {
  // synonym first arg, exact match ident second arg - select a (with operator)
  string query =
      "assign a; variable v;\n"
      "Select a pattern a(v,\"a + 1\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms2AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"7"};
  REQUIRE(result == expected);
}
