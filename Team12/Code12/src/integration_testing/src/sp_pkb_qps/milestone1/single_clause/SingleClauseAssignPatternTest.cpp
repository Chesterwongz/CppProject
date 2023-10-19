#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "pkb/facade/PKB.h"
#include "qps/QPS.h"
#include "sp/SourceProcessor.h"

using std::string, std::unordered_map, std::map, std::unordered_set, std::set,
    std::vector, std::pair;

string ms1AssignSource =
    "procedure AssignPattern {"
    "  line1 = 1 + 2 + 3 + 4;"
    "  line2 = a + b -c * d /  e %f;"
    "  if ((line3 + 1) == (a + 1)) then {"
    "    line4 = 1;"
    "  } else {"
    "    line5 = a;"
    "    while ((((line6 )- 1) > (a - 1)) && (!(1 != 1))) {"
    "        line7 = a + 1;"
    "    }"
    "  }"
    "}";

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "1") {
  // wildcard first arg, partial match ident second arg
  string query =
      "assign a;\n"
      "Select a pattern a(_, _\"1\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "4", "7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "2") {
  // wildcard first arg, partial match ident second arg version 2
  string query =
      "assign a;\n"
      "Select a pattern a(_, _\"a\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2", "5", "7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "3") {
  // wildcard first arg, partial match ident second arg version 3 - no results
  string query =
      "assign a;\n"
      "Select a pattern a(_, _\"huehue\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "4") {
  // wildcard first arg, partial match ident second arg
  // select different assign
  // return all assign statements since pattern evals to true
  string query =
      "assign a1, a2;\n"
      "Select a1 pattern a2(_, _\"a\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "2", "4", "5", "7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "5") {
  // wildcard first arg, partial match ident second arg
  // select different assign
  // return none since pattern evals to false
  string query =
      "assign a1, a2;\n"
      "Select a1 pattern a2(_, \"hehe\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "6") {
  // wildcard first arg, wildcard second arg
  string query =
      "assign a;\n"
      "Select a pattern a(_,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "2", "4", "5", "7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "7") {
  // ident first arg, partial match ident second arg
  string query =
      "assign a;\n"
      "Select a pattern a(\"line1\", _\"1\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "8") {
  // ident first arg, partial match ident second arg version 2
  string query =
      "assign a;\n"
      "Select a pattern a(\"line2\", _\"a\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "9") {
  // ident first arg, partial match ident second arg version 3 - no results
  string query =
      "assign a;\n"
      "Select a pattern a(\"line1\", _\"12\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "10") {
  // ident first arg, partial match ident second arg version 4 - no results
  string query =
      "assign a;\n"
      "Select a pattern a(\"line2\", _\"ab\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "11") {
  // ident first arg, wildcard second arg
  string query =
      "assign a;\n"
      "Select a pattern a(\"line4\",_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "12") {
  // ident first arg, wildcard second arg version 2 - no results
  string query =
      "assign a; variable v;\n"
      "Select a pattern a(\"v\",_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "13") {
  // ident first arg, partial match ident second arg
  // select different assign
  // return all assign statements since pattern evals to true
  string query =
      "assign a1, a2;\n"
      "Select a1 pattern a2(\"line2\", _\"a\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "2", "4", "5", "7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "14") {
  // ident first arg, partial match ident second arg
  // select different assign
  // return none since pattern evals to false
  string query =
      "assign a1, a2;\n"
      "Select a1 pattern a2(\"line2\", _\"ab\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "15") {
  // synonym first arg, wildcard second arg - select v
  string query =
      "assign a; variable v;\n"
      "Select v pattern a(v,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"line1", "line2", "line4", "line5",
                                    "line7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "16") {
  // synonym first arg, wildcard second arg - select a
  string query =
      "assign a; variable v;\n"
      "Select a pattern a(v,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "2", "4", "5", "7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "17") {
  // synonym first arg, partial match ident second arg - select v
  string query =
      "assign a; variable v;\n"
      "Select v pattern a(v,_\"1\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"line1", "line4", "line7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "18") {
  // synonym first arg, partial match ident second arg - select a
  string query =
      "assign a; variable v;\n"
      "Select a pattern a(v,_\"1\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "4", "7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "19") {
  // synonym first arg, partial match ident second arg version 2 - select v
  string query =
      "assign a; variable v;\n"
      "Select v pattern a(v,_\"a\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"line2", "line5", "line7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "20") {
  string query =
      "assign a; variable v;\n"
      "Select v pattern a(v,_\"     a\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"line2", "line5", "line7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "21") {
  string query =
      "assign a; variable v;\n"
      "Select a pattern a(\"    v   \",_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "22") {
  string query =
      "assign a;\n"
      "Select a pattern a(_, _\"   a  "
      "    \"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ms1AssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2", "5", "7"};
  REQUIRE(result == expected);
}
