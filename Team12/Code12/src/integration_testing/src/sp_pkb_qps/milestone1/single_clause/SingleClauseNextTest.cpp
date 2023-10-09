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

string nextSource =
    "procedure Next {"
    "  read line1;"
    "  if (line2 > line2)then {"
    "    while((line3 < line3)&& ( line3 == line3)){"
    "      print line4;"
    "    }"
    "    call Potato;"
    "  } else {"
    "  call Potato;"
    "  assign = line7;"
    "  }"
    "  assign = line8;"
    "}"
    "procedure Potato {"
    "  assign = line9;"
    "}";

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 1") {
  string query =
      "stmt Next;\n"
      "Select Next such that Next (_,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 2") {
  string query =
      "stmt stmt;\n"
      "Select stmt such that Next (stmt ,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "3", "4", "5", "6", "7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 3") {
  string query =
      "stmt Select;\n"
      "Select Select such that Next (_,Select)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "3", "4", "5", "6", "7", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 4") {
  string query =
      "stmt s, S;\n"
      "Select s such that Next (s,s)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 5") {
  string query =
      "stmt s, S;\n"
      "Select s such that Next (s,S)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "3", "4", "5", "6", "7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 6") {
  string query =
      "if Next;\n"
      "Select Next such that Next   ( 1,Next )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 7") {
  string query =
      "stmt Next;\n"
      "Select Next such that Next   ( 2,Next )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"3", "6"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 8") {
  string query =
      "stmt Next;\n"
      "Select Next such that Next   ( 4,Next )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"3"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 9") {
  string query =
      "stmt if;\n"
      "Select if such that Next   ( if,3 )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "4"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 10") {
  string query =
      "procedure p;\n"
      "Select p such that Next   ( 4,3 )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"Next", "Potato"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 11") {
  string query =
      "procedure p;\n"
      "Select p such that Next   ( 4,5 )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 12") {
  string query =
      "stmt s;\n"
      "Select s such that Next(2,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 13") {
  string query =
      "stmt s;\n"
      "Select s such that Next(5,9)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 14") {
  string query =
      "stmt s;\n"
      "Select s such that Next   ( _,1 )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 15") {
  string query =
      "print p;\n"
      "Select p such that Next( _,p)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"4"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 16") {
  string query =
      "print pn;\n"
      "Select pn such that Next ( pn,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"4"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 17") {
  string query =
      "stmt s;assign a;\n"
      "Select a such that Next( s,a )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"7", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/Next_queries.txt - 18") {
  string query =
      "stmt s;\n"
      "Select s such that Next( Next,_ )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(nextSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  // this is SemanticError because it is an undeclared synonym
  set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}
