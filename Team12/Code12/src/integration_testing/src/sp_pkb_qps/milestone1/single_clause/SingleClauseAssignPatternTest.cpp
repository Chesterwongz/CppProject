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

string assignSource =
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "2") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "3") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "4") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "5") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "6") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "7") {
  string query =
      "assign a;\n"
      "Select a pattern a(\"line1\", _\"12\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(assignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "8") {
  string query =
      "assign a;\n"
      "Select a pattern a(\"line2\", _\"ab\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(assignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "9") {
  string query =
      "assign a; variable v;\n"
      "Select a pattern a(\"v\",_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(assignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "10") {
  string query =
      "assign a; variable v;\n"
      "Select v pattern a(v,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(assignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"line1", "line2", "line4", "line5", "line7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "11") {
  string query =
      "assign a; variable v;\n"
      "Select v pattern a(v,_\"1\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(assignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"line1", "line4", "line7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/AssignPattern_queries.txt - "
    "12") {
  string query =
      "assign a; variable v;\n"
      "Select v pattern a(v,_\"a\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(assignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"line2", "line5", "line7"};
  REQUIRE(result == expected);
}
