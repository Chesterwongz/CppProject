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

string tupleSelectSource =
    "procedure procedure {\n"
    "  read line1;\n"
    "  call PotatoLine2;"
    "  print line3;\n"
    "  while (line4 != line4) {\n"
    "    if ((line5 == if) && ( ! (if >= if))) then{\n"
    "      line6 = variable + 5;\n"
    "      if ((line7 < if2) && ( ! (if2 > if2))) then {\n"
    "        read line8;\n"
    "        print line9;\n"
    "        while ((line10 > while2)&&(!(while2<while2))) {\n"
    "          line11 = variable2 + 10;\n"
    "        }"
    "      } else {"
    "        read line12;\n"
    "      } "
    "    } else {"
    "      read line13;"
    "    }"
    "  }"
    "}"
    "procedure PotatoLine2 {"
    "  line14 = 14;"
    "}";
// 3 assign
// 1 call
// 3 constants
// 2 ifs

TEST_CASE("SP-PKB-QPS integration - select tuples ASSIGN - 1") {
  string query =
      "assign assign1, assign2;\n"
      "Select <assign1, assign2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = { "11 11", "11 14", "11 6", "14 11", "14 14", "14 6", "6 11", "6 14", "6 6" };
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - select tuples CALL - 2") {
  string query =
      "call call1, call2;\n"
      "Select <call1, call2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"2", "2"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - select tuples CONSTANT - 3") {
  string query =
      "constant constant1, constant2;\n"
      "Select <constant1, constant2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = { "10 10", "10 14", "10 5", "14 10", "14 14", "14 5", "5 10", "5 14", "5 5" };
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - select tuples IF - 4") {
  string query =
      "if if1, if2;\n"
      "Select <if1, if2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = { "5 5", "5 7", "7 5", "7 7" };
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - select tuples PRINT - 5") {
  string query =
      "print print1, print2;\n"
      "Select <print1, print2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1 1", "12 12", "13 13", "8 8"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - select tuples PROCEDURE - 6") {
  string query =
      "procedure procedure1, procedure2;\n"
      "Select <procedure1, procedure2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1 1", "12 12", "13 13", "8 8"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - select tuples READ - 7") {
  string query =
      "read read1, read2;\n"
      "Select <read1, read2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1 1", "12 12", "13 13", "8 8"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - select tuples STMT - 8") {
  string query =
      "stmt stmt1, stmt2;\n"
      "Select <stmt1, stmt2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1 1", "12 12", "13 13", "8 8"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - select tuples VARIABLE - 9") {
  string query =
      "variable variable1, variable2;\n"
      "Select <variable1, variable2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1 1", "12 12", "13 13", "8 8"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - select tuples WHILE - 10") {
  string query =
      "while while1, while2;\n"
      "Select <while1, while2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"1 1", "12 12", "13 13", "8 8"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - select tuples READ CALL - 11") {
  string query =
      "read read1; call call1;\n"
      "Select <read1, call1>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = { "1 2", "12 2", "13 2", "8 2" };
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - select tuples "
    "ASSIGN CALL CONSTANT PRINT PROCEDURE - 12") {
  string query =
      "assign assign; call call; constant constant; print print; procedure procedure;\n"
      "Select <assign, call, constant, print, procedure >";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(tupleSelectSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = { "11 2 10 3 PotatoLine2", "11 2 10 3 procedure", "11 2 10 9 PotatoLine2", "11 2 10 9 procedure", "11 2 14 3 PotatoLine2", "11 2 14 3 procedure", "11 2 14 9 PotatoLine2", "11 2 14 9 procedure", "11 2 5 3 PotatoLine2", "11 2 5 3 procedure", "11 2 5 9 PotatoLine2", "11 2 5 9 procedure", "14 2 10 3 PotatoLine2", "14 2 10 3 procedure", "14 2 10 9 PotatoLine2", "14 2 10 9 procedure", "14 2 14 3 PotatoLine2", "14 2 14 3 procedure", "14 2 14 9 PotatoLine2", "14 2 14 9 procedure", "14 2 5 3 PotatoLine2", "14 2 5 3 procedure", "14 2 5 9 PotatoLine2", "14 2 5 9 procedure", "6 2 10 3 PotatoLine2", "6 2 10 3 procedure", "6 2 10 9 PotatoLine2", "6 2 10 9 procedure", "6 2 14 3 PotatoLine2", "6 2 14 3 procedure", "6 2 14 9 PotatoLine2", "6 2 14 9 procedure", "6 2 5 3 PotatoLine2", "6 2 5 3 procedure", "6 2 5 9 PotatoLine2", "6 2 5 9 procedure" };
  REQUIRE(result == expected);
}

