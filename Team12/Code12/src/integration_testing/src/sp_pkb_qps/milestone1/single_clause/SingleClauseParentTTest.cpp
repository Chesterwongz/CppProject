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

string parentStarSource =
    "procedure Parent {    read line1;"
    "    if (line2 > line2) then{"
    "        while((line3 <= line3)&& ( line3 == line3)){"
    "            read line4;"
    "            print line5;"
    "            if (line6 > line6) then{"
    "                if ((line7 * 7 == (line7 + 7)%7)||(! ( line7/line7 != "
    "line7/line7+7)))then{"
    "                  assign8 = line8;"
    "                  assign9 = line9 * 9 + (9) * (line9 / line9);"
    "                } else {"
    "                    while(line10 < line10){"
    "                        while((line11 < line11)&& ( line11 == line11)){"
    "                            print line12;"
    "                        }"
    "                    }"
    "                }"
    "            } else {"
    "                if (line13 > line13) then{"
    "                    while((line14) < (line14)){"
    "                      read line15;"
    "                    }"
    "                } else {"
    "                    assign16 = line16/16;"
    "                }"
    "            }"
    "        }"
    "    } else {"
    "        print line17;"
    "    }"
    "    assign18 = line18;"
    "}";

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 1") {
  string query =
      "stmt Follows;\n"
      "Select Follows such that Parent*(_,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",
                          "10", "11", "12", "13", "14", "15", "16", "17", "18"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 2") {
  string query =
      "stmt stmt;\n"
      "Select stmt such that Parent *(stmt ,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "3", "6", "7", "10", "11", "13", "14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 3") {
  string query =
      "stmt Select;\n"
      "Select Select such that Parent* (_,Select)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"3",  "4",  "5",  "6",  "7",  "8",  "9", "10",
                          "11", "12", "13", "14", "15", "16", "17"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 4") {
  string query =
      "stmt s, S;\n"
      "Select s such that Parent *(s,S)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "3", "6", "7", "10", "11", "13", "14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 5") {
  string query =
      "print Parent;\n"
      "Select Parent such that Parent*(2,Parent )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"5", "12", "17"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 6") {
  string query =
      "if if;\n"
      "Select if such that Parent  * ( if,7 )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "6"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 7") {
  string query =
      "procedure p;\n"
      "Select p such that Parent*(3,8)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"Parent"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 8") {
  string query =
      "assign a; while w;\n"
      "Select a such that Parent*(w,a)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"8", "9", "16"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 9") {
  string query =
      "stmt s;\n"
      "Select s such that Parent*(5,_ )";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 10") {
  string query =
      "read read;\n"
      "Select read such that Parent *( _,18)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 11") {
  string query =
      "assign Parent;\n"
      "Select Parent such that Parent*( _,Parent)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"8", "9", "16"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 12") {
  string query =
      "print pn;\n"
      "Select pn such that Parent* ( pn,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 13") {
  string query =
      "stmt s; print read;\n"
      "Select read such that Parent *(read,s)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 14") {
  string query =
      "if while; while w;\n"
      "Select while such that Parent* (while,w)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "6", "7", "13"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 15") {
  string query =
      "if if; while w;\n"
      "Select if such that Parent* (w,if)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"6", "7", "13"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 16") {
  string query =
      "if if1; if if2;\n"
      "Select if1 such that Parent *(if1,if2)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "6"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 17") {
  string query =
      "if if1, if, if2;\n"
      "Select if2 such that Parent*(if1,if2)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"6", "7", "13"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 18") {
  string query =
      "if if; while w;\n"
      "Select w such that Parent*(if,w)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"3", "10", "11", "14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 19") {
  string query =
      "if if; while w;\n"
      "Select w such that Parent* (w,if)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"3"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 20") {
  string query =
      "while w; stmt s;\n"
      "Select s such that Parent*(s,w)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "3", "6", "7", "10", "13"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone1/SingleClauseTests/ParentT_queries.txt - 21") {
  string query =
      "while w; stmt s;\n"
      "Select s such that Parent*(w,s)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(parentStarSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"4",  "5",  "6",  "7",  "8",  "9", "10",
                          "11", "12", "13", "14", "15", "16"};
  REQUIRE(result == expected);
}
