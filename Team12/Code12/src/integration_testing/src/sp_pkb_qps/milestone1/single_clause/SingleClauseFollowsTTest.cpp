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

string followsStarSource =
    "procedure FollowsT {"
    "  read line1;"
    "  if (line2 > line2)then {"
    "  while((line3 < line3)&& ( line3 == line3)){"
    "    print line4;"
    "    assign5 = line5;"
    "  }"
    "      read line6;"
    "  } else {"
    "    assign7 = line7;"
    "  }"
    "  assign8 = line8;"
    "}";

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 1") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 2") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 3") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 4") {
  string query =
      "stmt s, S;\n"
      "Select s such that Follows *(s,s)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 5") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 6") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 7") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 8") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 9") {
  string query =
      "stmt s;\n"
      "Select s such that Follows*(2,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "3", "4", "5", "6", "7", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 10") {
  string query =
      "stmt s;\n"
      "Select s such that Follows*(5,_ )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 11") {
  string query =
      "stmt s;\n"
      "Select s such that Follows   *( _,4 )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 12") {
  string query =
      "print p;\n"
      "Select p such that Follows*( _,p)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 13") {
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

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/FollowsT_queries.txt - 14") {
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
