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

string source =
    "procedure WithSource1 {"
    "  if (x<0) then {"
    "    while (100>hihi) {"
    "      x = z * 3 + 2 * y;"
    "      print q;"
    "      i = i - 1; }"
    "    x = x + 1;"
    "    z = x + z; }"
    "  else {"
    "    z = 1; }"
    "  lalala = 200;"
    "  z = z + x + i; }"
    ""
    "procedure WithSource2 {"
    "  while (i!=0) {"
    "    x = x - 1;"
    "    if (hello==1) then {"
    "      z = x + 1; }"
    "    else {"
    "      y = z + x;"
    "      call WithSource1; }"
    "    z = z + x + i;"
    "    read q; }"
    "  lololol = 100;"
    "  print p;"
    "  call WithSource3;}"
    ""
    "procedure WithSource3 {"
    "  print wow;"
    "  read amazing;"
    "  WithSource1 = 100;"
    "}";

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "1") {
  string query =
      "assign a;\n"
      "Select a with a.stmt# = 5";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"5"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "2") {
  string query =
      "assign a;\n"
      "Select a with a.stmt# = 2";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "3") {
  string query =
      "assign a1, a2;\n"
      "Select a1 with a2.stmt# = 5";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"3",  "5",  "6",  "7",  "8",  "9", "10",
                                    "12", "14", "15", "17", "19", "24"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "4") {
  string query =
      "assign a1, a2;\n"
      "Select a1 with a2.stmt# = 11";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "5") {
  string query =
      "if i;\n"
      "Select i with i.stmt# = 1";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "6") {
  string query =
      "if i;\n"
      "Select i with i.stmt# = 2";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "7") {
  string query =
      "if i1, i2;\n"
      "Select i1 with i2.stmt# = 13";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "13"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "8") {
  string query =
      "if i1, i2;\n"
      "Select i1 with i2.stmt# = 10";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "9") {
  string query =
      "while w;\n"
      "Select w with w.stmt# = 2";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "10") {
  string query =
      "while w;\n"
      "Select w with w.stmt# = 1";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "11") {
  string query =
      "while w1, w2;\n"
      "Select w1 with w2.stmt# = 11";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2", "11"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "12") {
  string query =
      "while w1, w2;\n"
      "Select w1 with w2.stmt# = 12";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "13") {
  string query =
      "stmt s;\n"
      "Select s with s.stmt# = 15";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"15"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "14") {
  string query =
      "stmt s;\n"
      "Select s with s.stmt# = 100";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "15") {
  string query =
      "stmt s1, s2;\n"
      "Select s1 with s2.stmt# = 1";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "10", "11", "12",
      "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "16") {
  string query =
      "stmt s1, s2;\n"
      "Select s1 with s2.stmt# = 25";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "17") {
  string query =
      "constant const;\n"
      "Select const with const.value = 100";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"100"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "18") {
  string query =
      "constant const;\n"
      "Select const with const.value = 5";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "19") {
  string query =
      "constant const1, const2;\n"
      "Select const1 with const2.value = 1";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"0", "1", "2", "3", "100", "200"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "20") {
  string query =
      "constant const1, const2;\n"
      "Select const1 with const2.value = 222";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "21") {
  string query =
      "procedure p;\n"
      "Select p with p.procName = \"WithSource1\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"WithSource1"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "22") {
  string query =
      "procedure p;\n"
      "Select p with p.procName = \"withSource3\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "23") {
  string query =
      "procedure p1, p2;\n"
      "Select p1 with p2.procName = \"WithSource2\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"WithSource1", "WithSource2",
                                    "WithSource3"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "24") {
  string query =
      "procedure p1, p2;\n"
      "Select p1 with p2.procName = \"withSource3\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "25") {
  string query =
      "variable v;\n"
      "Select v with v.varName = \"x\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"x"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "26") {
  string query =
      "variable v;\n"
      "Select v with v.varName = \"iDontExist\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "27") {
  string query =
      "variable v1, v2;\n"
      "Select v1 with v2.varName = \"lalala\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "i",       "p",   "q",       "x",    "y",     "z",          "lalala",
      "lololol", "wow", "amazing", "hihi", "hello", "WithSource1"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "28") {
  string query =
      "variable v1, v2;\n"
      "Select v1 with v2.varName = \"lalalal\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "29") {
  string query =
      "call c;\n"
      "Select c with c.stmt# = 16";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"16"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "30") {
  string query =
      "call c;\n"
      "Select c with c.stmt# = 17";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "31") {
  string query =
      "call c1, c2;\n"
      "Select c1 with c2.stmt# = 16";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"16", "21"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "32") {
  string query =
      "call c1, c2;\n"
      "Select c1 with c2.stmt# = 1";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "33") {
  string query =
      "call c;\n"
      "Select c with c.procName = \"WithSource3\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"21"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "34") {
  string query =
      "call c;\n"
      "Select c with c.procName = \"WithSource2\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "35") {
  string query =
      "call c1, c2;\n"
      "Select c1 with c2.procName = \"WithSource1\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"16", "21"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "36") {
  string query =
      "call c1, c2;\n"
      "Select c1 with c2.procName = \"WithSource2\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "37") {
  string query =
      "read r;\n"
      "Select r with r.stmt# = 23";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"23"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "38") {
  string query =
      "read r;\n"
      "Select r with r.stmt# = 22";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "39") {
  string query =
      "read r1, r2;\n"
      "Select r1 with r2.stmt# = 18";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"18", "23"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "40") {
  string query =
      "read r1, r2;\n"
      "Select r1 with r2.stmt# = 19";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "41") {
  string query =
      "read r;\n"
      "Select r with r.varName = \"amazing\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"23"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "42") {
  string query =
      "read r;\n"
      "Select r with r.varName = \"notAmazing\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "43") {
  string query =
      "read r;\n"
      "Select r with r.varName = \"q\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"18"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "44") {
  string query =
      "read r;\n"
      "Select r with r.varName = \"q1\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "45") {
  string query =
      "print pn;\n"
      "Select pn with pn.stmt# = 4";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "46") {
  string query =
      "print pn;\n"
      "Select pn with pn.stmt# = 5";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "47") {
  string query =
      "print pn1, pn2;\n"
      "Select pn1 with pn2.stmt# = 22";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "20", "22"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "48") {
  string query =
      "print pn1, pn2;\n"
      "Select pn1 with pn2.stmt# = 23";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "49") {
  string query =
      "print pn;\n"
      "Select pn with pn.varName = \"wow\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"22"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "50") {
  string query =
      "print pn;\n"
      "Select pn with pn.varName = \"notWow\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "51") {
  string query =
      "print pn1, pn2;\n"
      "Select pn1 with pn2.varName = \"p\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "20", "22"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "52") {
  string query =
      "print pn1, pn2;\n"
      "Select pn1 with pn2.varName = \"XD\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "53") {
  string query =
      "assign a;\n"
      "Select a with a.varName = \"x\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "54") {
  string query =
      "if i;\n"
      "Select i with i.procName = \"WithSource1\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "55") {
  string query =
      "while w;\n"
      "Select w with w.varName = \"hihi\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "56") {
  string query =
      "call c;\n"
      "Select c with c.value = 1";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "57") {
  string query =
      "print pn;\n"
      "Select pn with pn.procName = \"wow\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "58") {
  string query =
      "read r;\n"
      "Select r with r.procName = \"amazing\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "59") {
  string query =
      "stmt s;\n"
      "Select s with s.varName = \"z\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "60") {
  string query =
      "constant const;\n"
      "Select const with const.stmt# = 3";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "61") {
  string query =
      "procedure p;\n"
      "Select p with p.varName = \"x\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "62") {
  string query =
      "variable v;\n"
      "Select v with v.stmt# = 6";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "63") {
  string query =
      "assign a; procedure p;\n"
      "Select p with a.stmt# = a.stmt#";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"WithSource1", "WithSource2",
                                    "WithSource3"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "64") {
  string query =
      "assign a1, a2; procedure p;\n"
      "Select p with a1.stmt# = a2.stmt#";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"WithSource1", "WithSource2",
                                    "WithSource3"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "65") {
  string query =
      "variable v; procedure p;\n"
      "Select v with v.varName = p.procName";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"WithSource1"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "66") {
  string query =
      "call c; stmt s;\n"
      "Select s with c.procName = c.stmt#";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "67") {
  string query =
      "stmt s;\n"
      "Select s with 3 = 3";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "10", "11", "12",
      "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "68") {
  string query =
      "stmt s;\n"
      "Select s with 3 = 4";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "69") {
  string query =
      "stmt s;\n"
      "Select s with \"samesame\" = \"samesame\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "10", "11", "12",
      "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "70") {
  string query =
      "stmt s;\n"
      "Select s with \"samesame\" = \"samesamebutdifferent\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "71") {
  string query =
      "stmt s;\n"
      "Select s with \"samesame\" = 100";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "72") {
  string query = "stmt s; Select BOOLEAN with s.stmt# = \"1\"";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SyntaxError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "73") {
  string query = R"(Select BOOLEAN with "x z" = "y")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SyntaxError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "74") {
  string query = R"(stmt s; Select s with "s" = "s")";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "10", "11", "12",
      "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24"};
  REQUIRE(result == expected);
}


TEST_CASE(
    "SP-PKB-QPS ../../Tests12/Milestone2/SingleClauseTests/With_queries.txt - "
    "75") {
  string query = "Select";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(source, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SyntaxError"};
  REQUIRE(result == expected);
}
