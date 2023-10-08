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

string ifSource = 
    "procedure p {"
      "if (1 == 2) then {"        // 1
        "while (hoho == 4) {"     // 2
          "x = 1;"                // 3
        "}"
      "}"
      "else {"
        "if (hoho == 1) then {"   // 4
          "while (hehe == x) {"   // 5
            "z = 2;"              // 6
          "}"
        "}"
        "else {"
          "y = 3;"                // 7
        "}"
      "}"
      "if (oi == 11) then {"      // 8
        "oi = oi + 1;"            // 9
      "}"
      "else {"
        "while (oi == 2) {"       // 10
          "oi = oi - 1;"          // 11
        "}"
      "}"
    "}";


TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/ifPattern_queries.txt - "
    "1") {
  // wildcard first arg - return all if statments that use a variable
  string query =
      "if if;\n"
      "Select if pattern if(_, _, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ifSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "4", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/ifPattern_queries.txt - "
    "2") {
  // wildcard first arg, but select different if - return all if statments
  string query =
      "if if1, if2;\n"
      "Select if1 pattern if2(_, _, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ifSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "4", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/ifPattern_queries.txt - "
    "3") {
  // synonym first arg - return all if statements that use a variable
  string query =
      "if if; variable v;\n"
      "Select if pattern if(v, _, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ifSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "4", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/ifPattern_queries.txt - "
    "4") {
  // synonym first arg, but select different if - return all if statments
  string query =
      "if if1, if2; variable d;\n"
      "Select if1 pattern if2(d, _, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ifSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "4", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/ifPattern_queries.txt - "
    "5") {
  // ident first arg - return all if statements that use specific ident
  string query =
      "if if;\n"
      "Select if pattern if(\"oi\", _, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ifSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/ifPattern_queries.txt - "
    "6") {
  // ident first arg, but select different if - return all if statments
  // since an if statement that uses "hoho" exists
  string query =
      "if if1, if2;\n"
      "Select if1 pattern if2(\"hoho\", _, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ifSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1", "2", "4", "8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS tests/Milestone2/SingleClauseTests/ifPattern_queries.txt - "
    "7") {
  // ident first arg, but select different if - return none
  // since an if statement that uses "hehe" DOES NOT exist
  string query =
      "if if1, if2;\n"
      "Select if1 pattern if2(\"hehe\", _, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(ifSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {};
  REQUIRE(result == expected);
}
