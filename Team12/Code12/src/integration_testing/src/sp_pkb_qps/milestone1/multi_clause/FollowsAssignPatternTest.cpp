#include <catch.hpp>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/QPS.h"
#include "sp/SourceProcessor.h"

using std::string, std::unordered_map, std::map, std::unordered_set, std::set,
    std::vector, std::pair;

string followsAssignSource =
    "procedure FollowsPattern{"
    "  read line1;"
    "  if (line2 > line2)then {"
    "  while((line3 < line3)&& ( line3 == line3)){"
    "    print line4;"
    "    assign5 = line5 + line5;"
    "  }"
    "      read line6;"
    "  } else {"
    "    assign7 = (line7+line7)/line7*line7-line7%(line7);"
    "  }"
    "  assign8 = line8;"
    "}";

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 1") {
  string query =
      "stmt stmt; assign Follows;\n"
      "Select stmt such that Follows (_,_) pattern Follows (_,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "3", "4", "5", "6", "7", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 2") {
  string query =
      "stmt Follows; assign stmt;\n"
      "Select Follows such that Follows (_,_) pattern stmt(\"NA\",_\"NA\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 3") {
  string query =
      "stmt stmt; assign a;\n"
      "Select stmt such that Follows (stmt ,_) pattern a(_,_\"line7\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "3", "4"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 4") {
  string query =
      "stmt stmt; assign a;\n"
      "Select stmt such that Follows (stmt ,_) pattern a(_,_\"NA\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 5") {
  string query =
      "stmt Select; assign a;\n"
      "Select Select such that Follows (_,Select) pattern a (\"assign8\", _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "5", "6", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 6") {
  string query =
      "stmt Select; assign a;\n"
      "Select Select such that Follows (_,Select) pattern a (\"NA\", _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 7") {
  string query =
      "stmt s, S;assign a;\n"
      "Select s such that Follows (s,s) pattern a (\"assign7\", _\"line7\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 8") {
  string query =
      "stmt s, S; assign a;\n"
      "Select s such that Follows (s,S) pattern a (\"assign7\", _\"line7\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "3", "4"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 9") {
  string query =
      "stmt s, S; assign a;\n"
      "Select s such that Follows (s,S) pattern a (\"assign7\", _\"7\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 10") {
  string query =
      "if Follows; assign a;\n"
      "Select Follows such that Follows   ( 1,Follows )pattern a (\"assign7\", "
      "_\"line7\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 11") {
  string query =
      "if Follows; assign a;\n"
      "Select Follows such that Follows   ( 1,Follows )pattern a (\"assign\", "
      "_\"line7\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 12") {
  string query =
      "procedure p; assign a;\n"
      "Select p such that Follows   ( 3,6 ) pattern a (\"assign7\", "
      "_\"line7\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"FollowsPattern"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 13") {
  string query =
      "procedure p; assign a;\n"
      "Select p such that Follows   ( 3,6 ) pattern a (\"assign5\", "
      "_\"line7\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 14") {
  string query =
      "stmt s; assign a; variable v; constant c;\n"
      "Select v such that Follows(2,_) pattern a(v, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"assign5", "assign7", "assign8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 15") {
  string query =
      "stmt s; assign a; variable v; constant c;\n"
      "Select v such that Follows(8,_) pattern a(v, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 16") {
  string query =
      "stmt s; assign a; variable v; constant c;\n"
      "Select v such that Follows(s, a  ) pattern a(v, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"assign5", "assign8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 17") {
  string query =
      "stmt s; assign a; variable v; constant c;\n"
      "Select v such that Follows(s,a) pattern a(v, _\"line8\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"assign8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 18") {
  string query =
      "stmt s;assign a;variable v;\n"
      "Select a such that Follows( s,a ) pattern a(v, _\"line5\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"5"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 19") {
  string query =
      "stmt s;assign a;variable v;\n"
      "Select a such that Follows( s,a ) pattern a(\"assign8\", _\"line5\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 20") {
  string query =
      "stmt s;assign a1, a2;variable v;\n"
      "Select a2 such that Follows( s,a1 ) pattern a2(v, _\"line5\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"5"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 21") {
  string query =
      "stmt s;assign a1, a2;\n"
      "Select a1 such that Follows( s,a1 ) pattern a2(_, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"5", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "tests/Milestone1/MultiClauseTests/FollowsAssignPattern_queries.txt - 22") {
  string query =
      "stmt s;assign a;variable v;\n"
      "Select a pattern a(v, _\"line5\"_)such that Follows( s,a )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(followsAssignSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"5"};
  REQUIRE(result == expected);
}
