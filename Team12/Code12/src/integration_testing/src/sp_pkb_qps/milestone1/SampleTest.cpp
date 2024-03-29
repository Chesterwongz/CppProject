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

string sampleSource =
    "procedure Example {"
    "  x = 2;"              // 1
    "  z = 3;"              // 2
    "  i = 5;"              // 3
    "  while (i!=0) {"      // 4
    "    x = x - 1;"        // 5
    "    if (x==1) then {"  // 6
    "      z = x + 1; }"    // 7
    "    else {"
    "      y = z + x; }"  // 8
    "    z = z + x + i;"  // 9
    "    read q;"         // 10
    "    i = i - 1; }"    // 11
    "  print p; }"        // 12
    ""
    "procedure p {"
    "  if (x<0) then {"         // 13
    "    while (i>0) {"         // 14
    "      x = z * 3 + 2 * y;"  // 15
    "      print q;"            // 16
    "      i = i - 1; }"        // 17
    "    x = x + 1;"            // 18
    "    z = x + z; }"          // 19
    "  else {"
    "    z = 1; }"        // 20
    "  z = z + x + i; }"  // 21
    ""
    "procedure q {"
    "  if (x==1) then {"  // 22
    "    z = x + 1; }"    // 23
    "  else {"
    "    x = z + x; } }";  // 24

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 1") {
  string query =
      "while w;\n"
      "Select w such that Parent(w, 7)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
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
  unordered_set<string> expected = {"6"};
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
  unordered_set<string> expected = {"5", "7", "8", "9", "11"};
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
  unordered_set<string> expected = {};
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
  unordered_set<string> expected = {"3", "4", "11", "13", "14", "17"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 6") {
  // get all assign statements that use some variable
  string query =
      "assign a; variable v;\n"
      "Select a such that Uses(a, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"5",  "7",  "8",  "9",  "11", "15",
                                    "17", "18", "19", "21", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 7") {
  // get all assign statements that use "x"
  string query =
      "assign a;\n"
      "Select a such that Uses(a, \"x\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"5",  "7",  "8",  "9", "18",
                                    "19", "21", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 8") {
  // get all assign statements that use some variable
  string query =
      "assign a;\n"
      "Select a such that Uses(a, _)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"5",  "7",  "8",  "9",  "11", "15",
                                    "17", "18", "19", "21", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 9") {
  // get all assign statements if there exists some assign statement that uses a
  // variable
  string query =
      "assign a1, a2; variable v;\n"
      "Select a1 such that Uses(a2, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1",  "2",  "3",  "5",  "7",  "8",
                                    "9",  "11", "15", "17", "18", "19",
                                    "20", "21", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 10") {
  // get all assign statements if there exists some assign statement that uses
  // "u"
  string query =
      "assign a1, a2; variable v;\n"
      "Select a1 such that Uses(a2, \"u\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 11") {
  // get all print statements that use some variable
  string query =
      "print pn; variable v;\n"
      "Select pn such that Uses(pn, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"12", "16"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 12") {
  // get all print statements that use "q"
  string query =
      "print pn;\n"
      "Select pn such that Uses(pn, \"q\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"16"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 13") {
  // get all print statements if there exists some print statement that uses
  // some variable
  string query =
      "print pn1, pn2; variable v;\n"
      "Select pn1 such that Uses(pn2, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"12", "16"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 14") {
  // get all print statements if there exists some print statement that uses "b"
  string query =
      "print pn1, pn2; variable v;\n"
      "Select pn1 such that Uses(pn2, \"b\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 15") {
  // get all while statements that use some variable
  string query =
      "while w; variable v;\n"
      "Select w such that Uses(w, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "14"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 16") {
  // get all while statements that use "i"
  string query =
      "while w;\n"
      "Select w such that Uses(w, \"i\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "14"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 17") {
  // get all while statements that use some variable
  string query =
      "while w;\n"
      "Select w such that Uses(w, _ )";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "14"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 18") {
  // get all while statements that if there exists some while statement that
  // uses a variable
  string query =
      "while w1, w2; variable v;\n"
      "Select w1 such that Uses(w2, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "14"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 19") {
  // get all while statements if there exists a while statement that uses "h"
  string query =
      "while w1, w2;\n"
      "Select w1 such that Uses(w2, \"h\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 20") {
  // get all if statements that use some variable
  string query =
      "if if; variable v;\n"
      "Select if such that Uses(if, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"6", "13", "22"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 21") {
  // get all if statements that use "y"
  string query =
      "if if;\n"
      "Select if such that Uses(if, \"y\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"13"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 22") {
  // get all if statements that use some variable
  string query =
      "if if;\n"
      "Select if such that Uses(if, _ )";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"6", "13", "22"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 23") {
  // get all if statements if there exists some if statement that uses a
  // variable
  string query =
      "if if1, if2; variable v;\n"
      "Select if1 such that Uses(if2, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"6", "13", "22"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 24") {
  // get all if statements if there exists an if statement that uses "g"
  string query =
      "if if1, if2;\n"
      "Select if1 such that Uses(if2, \"g\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 25") {
  // get all statements that use some variable
  string query =
      "stmt s; variable v;\n"
      "Select s such that Uses(s, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4",  "5",  "6",  "7",  "8",  "9",  "11",
                                    "12", "13", "14", "15", "16", "17", "18",
                                    "19", "21", "22", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 26") {
  // get all statements that use "y"
  string query =
      "stmt s;\n"
      "Select s such that Uses(s, \"y\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"13", "14", "15"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 27") {
  // get all statements that use some variable
  string query =
      "stmt s;\n"
      "Select s such that Uses(s, _ )";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4",  "5",  "6",  "7",  "8",  "9",  "11",
                                    "12", "13", "14", "15", "16", "17", "18",
                                    "19", "21", "22", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 28") {
  // get all statements if there exists some statement that uses a variable
  string query =
      "stmt s1, s2; variable v;\n"
      "Select s1 such that Uses(s2, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "10", "11", "12",
      "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 29") {
  // get all statements if there exists a statement that uses "g"
  string query =
      "stmt s1, s2;\n"
      "Select s1 such that Uses(s2, \"g\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 30") {
  // get all assign statements that modify some variable
  string query =
      "assign a; variable v;\n"
      "Select a such that Modifies(a, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1",  "2",  "3",  "5",  "7",  "8",
                                    "9",  "11", "15", "17", "18", "19",
                                    "20", "21", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 31") {
  // get all assign statements that modify "x"
  string query =
      "assign a;\n"
      "Select a such that Modifies(a, \"x\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "5", "15", "18", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 32") {
  // get all assign statements that modify some variable
  string query =
      "assign a;\n"
      "Select a such that Modifies(a, _)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1",  "2",  "3",  "5",  "7",  "8",
                                    "9",  "11", "15", "17", "18", "19",
                                    "20", "21", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 33") {
  // get all assign statements if there exists some assign statement that
  // modifies a variable
  string query =
      "assign a1, a2; variable v;\n"
      "Select a1 such that Modifies(a2, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1",  "2",  "3",  "5",  "7",  "8",
                                    "9",  "11", "15", "17", "18", "19",
                                    "20", "21", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 34") {
  // get all assign statements if there exists some assign statement that
  // Modifies "u"
  string query =
      "assign a1, a2;\n"
      "Select a1 such that Modifies(a2, \"u\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 35") {
  // get all read statements that modify some variable
  string query =
      "read re; variable v;\n"
      "Select re such that Modifies(re, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"10"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 36") {
  // get all read statements that modify "q"
  string query =
      "read re;\n"
      "Select re such that Modifies(re, \"q\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"10"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 37") {
  // get all read statements that modify some variable
  string query =
      "read re;\n"
      "Select re such that Modifies(re, _)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"10"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 38") {
  // get all read statements if there exists some read statement that modifies a
  // variable
  string query =
      "read re1, re2; variable v;\n"
      "Select re1 such that Modifies(re2, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"10"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 39") {
  // get all read statements if there exists some read statement that Modifies
  // "u"
  string query =
      "read re1, re2;\n"
      "Select re1 such that Modifies(re2, \"u\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 40") {
  // get all while statements that modify some variable
  string query =
      "while w; variable v;\n"
      "Select w such that Modifies(w, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "14"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 41") {
  // get all while statements that modify "r"
  string query =
      "while w;\n"
      "Select w such that Modifies(w, \"r\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 42") {
  // get all while statements that modify some variable
  string query =
      "while w;\n"
      "Select w such that Modifies(w, _)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "14"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 43") {
  // get all while statements if there exists some while statement that modifies
  // a variable
  string query =
      "while w1, w2; variable v;\n"
      "Select w1 such that Modifies(w2, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "14"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 44") {
  // get all while statements if there exists some while statement that Modifies
  // "w"
  string query =
      "while w1, w2;\n"
      "Select w1 such that Modifies(w2, \"w\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 45") {
  // get all if statements that modify some variable
  string query =
      "if if; variable v;\n"
      "Select if such that Modifies(if, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"6", "13", "22"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 46") {
  // get all if statements that modify "y"
  string query =
      "if if;\n"
      "Select if such that Modifies(if, \"y\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"6"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 47") {
  // get all if statements that modify some variable
  string query =
      "if if;\n"
      "Select if such that Modifies(if, _)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"6", "13", "22"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 48") {
  // get all if statements if there exists some if statement that modifies a
  // variable
  string query =
      "if if1, if2; variable v;\n"
      "Select if1 such that Modifies(if2, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"6", "13", "22"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 49") {
  // get all if statements if there exists some if statement that Modifies "w"
  string query =
      "if if1, if2;\n"
      "Select if1 such that Modifies(if2, \"w\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 50") {
  // get all statements that modify some variable
  string query =
      "stmt s; variable v;\n"
      "Select s such that Modifies(s, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "10", "11",
      "13", "14", "15", "17", "18", "19", "20", "21", "22", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 51") {
  // get all statements that modify "z"
  string query =
      "stmt s;\n"
      "Select s such that Modifies(s, \"z\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2",  "4",  "6",  "7",  "9", "13",
                                    "19", "20", "21", "22", "23"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 52") {
  // get all statements that modify some variable
  string query =
      "stmt s;\n"
      "Select s such that Modifies(s, _)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "10", "11",
      "13", "14", "15", "17", "18", "19", "20", "21", "22", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 53") {
  // get all statements if there exists some statement that modifies a variable
  string query =
      "stmt s1, s2; variable v;\n"
      "Select s1 such that Modifies(s2, v)";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "10", "11", "12",
      "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 54") {
  // get all statements there exists some if statement that Modifies "j"
  string query =
      "stmt s1, s2;\n"
      "Select s1 such that Modifies(s2, \"j\")";

  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 55") {
  string query =
      "procedure p;\n"
      "Select p such that Calls(p, \"q\")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 56") {
  string query =
      "procedure p;\n"
      "Select p such that Calls*(\"Example\", p)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 57") {
  string query =
      "stmt n;\n"
      "Select n such that Next(4, n)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"5", "12"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 58") {
  string query =
      "stmt n;\n"
      "Select n such that Next*(n, 4)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "2", "3", "4",  "5", "6",
                                    "7", "8", "9", "10", "11"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 59") {
  string query =
      "assign a;\n"
      "Select a such that Affects(a, 9)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2", "3", "5", "7", "9", "11"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 61") {
  string query =
      "assign a;\n"
      "Select a pattern a(\"z\", _\"x+i\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 62") {
  string query =
      "assign a;\n"
      "Select a pattern a(_, _\"x + 1\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"7", "18", "23"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 63") {
  string query =
      "assign a;\n"
      "Select a pattern a(_, \" 3  +  2 \")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 64") {
  string query =
      "while w; variable v;\n"
      "Select w such that Modifies(w, v) with v.varName = \"x\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "14"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 65") {
  string query =
      "if ifs; variable v;\n"
      "Select v such that Uses(ifs, v) with ifs.stmt# = 22";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"x", "z"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 67") {
  string query =
      "if ifs; assign a1, a2; variable v1, v2;\n"
      "Select ifs such that Follows*(a1, ifs) and Follows*(ifs, a2) and "
      "Modifies(ifs, v1) and Uses(ifs, v2) with v1.varName = v2.varName";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"6"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS tests/Sample_queries.txt - 68") {
  string query =
      "stmt n; stmt s;\n"
      "Select s such that Next*(16, n) and Parent*(s, n)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sampleSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"13", "14"};
  REQUIRE(result == expected);
}
