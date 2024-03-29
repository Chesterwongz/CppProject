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

string selectTuplePatternSource =
    "procedure procedure {\n"
    "  read line1;\n"
    "  call PotatoLine2;\n"
    "  print line3;\n"
    "  while (line4 != line4) {\n"
    "    if ((line5 == if) && ( ! (if >= if))) then{\n"
    "      line6 = variable + 5;\n"
    "      if ((line7 < if2) && ( ! (if2 > if2))) then {\n"
    "        read line8;\n"
    "        print line9;\n"
    "        while ((line10 > while2)&&(!(while2<while2))) {\n"
    "          line11 = variable2 + 10;\n"
    "        }\n"
    "      } else {\n"
    "        read line12;\n"
    "      } \n"
    "    } else {\n"
    "      read line13;\n"
    "    }\n"
    "  }\n"
    "}\n"
    "procedure PotatoLine2 {\n"
    "  line14 = 14;\n"
    "}\n";
// 3 assign | 1 call | 3 constants | 2 ifs | 2 prints
// 2 procedures | 4 reads | 14 stmts | 16 variables | 2 whiles

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 1") {
  string query =
      "assign assign1, assign2;\n"
      "Select <assign1, assign2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"11 11", "11 14", "11 6", "14 11", "14 14",
                                    "14 6",  "6 11",  "6 14", "6 6"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 2") {
  string query =
      "call call1, call2;\n"
      "Select <call1, call2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2 2"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 3") {
  string query =
      "constant constant1, constant2;\n"
      "Select <constant1, constant2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"10 10", "10 14", "10 5", "14 10", "14 14",
                                    "14 5",  "5 10",  "5 14", "5 5"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 4") {
  string query =
      "if if1, if2;\n"
      "Select <if1, if2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"5 5", "5 7", "7 5", "7 7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 5") {
  string query =
      "print print1, print2;\n"
      "Select <print1, print2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"3 3", "3 9", "9 3", "9 9"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 6") {
  string query =
      "procedure procedure1, procedure2;\n"
      "Select <procedure1, procedure2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "PotatoLine2 PotatoLine2", "PotatoLine2 procedure",
      "procedure PotatoLine2", "procedure procedure"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 7") {
  string query =
      "read read1, read2;\n"
      "Select <read1, read2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "1 1",  "1 12",  "1 13",  "1 8",  "12 1", "12 12", "12 13", "12 8",
      "13 1", "13 12", "13 13", "13 8", "8 1",  "8 12",  "8 13",  "8 8"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 8") {
  string query =
      "stmt stmt1, stmt2;\n"
      "Select <stmt1, stmt2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "1 1",   "1 2",   "1 3",   "1 4",   "1 5",   "1 6",   "1 7",   "1 8",
      "1 9",   "1 10",  "1 11",  "1 12",  "1 13",  "1 14",  "2 1",   "2 2",
      "2 3",   "2 4",   "2 5",   "2 6",   "2 7",   "2 8",   "2 9",   "2 10",
      "2 11",  "2 12",  "2 13",  "2 14",  "3 1",   "3 2",   "3 3",   "3 4",
      "3 5",   "3 6",   "3 7",   "3 8",   "3 9",   "3 10",  "3 11",  "3 12",
      "3 13",  "3 14",  "4 1",   "4 2",   "4 3",   "4 4",   "4 5",   "4 6",
      "4 7",   "4 8",   "4 9",   "4 10",  "4 11",  "4 12",  "4 13",  "4 14",
      "5 1",   "5 2",   "5 3",   "5 4",   "5 5",   "5 6",   "5 7",   "5 8",
      "5 9",   "5 10",  "5 11",  "5 12",  "5 13",  "5 14",  "6 1",   "6 2",
      "6 3",   "6 4",   "6 5",   "6 6",   "6 7",   "6 8",   "6 9",   "6 10",
      "6 11",  "6 12",  "6 13",  "6 14",  "7 1",   "7 2",   "7 3",   "7 4",
      "7 5",   "7 6",   "7 7",   "7 8",   "7 9",   "7 10",  "7 11",  "7 12",
      "7 13",  "7 14",  "8 1",   "8 2",   "8 3",   "8 4",   "8 5",   "8 6",
      "8 7",   "8 8",   "8 9",   "8 10",  "8 11",  "8 12",  "8 13",  "8 14",
      "9 1",   "9 2",   "9 3",   "9 4",   "9 5",   "9 6",   "9 7",   "9 8",
      "9 9",   "9 10",  "9 11",  "9 12",  "9 13",  "9 14",  "10 1",  "10 2",
      "10 3",  "10 4",  "10 5",  "10 6",  "10 7",  "10 8",  "10 9",  "10 10",
      "10 11", "10 12", "10 13", "10 14", "11 1",  "11 2",  "11 3",  "11 4",
      "11 5",  "11 6",  "11 7",  "11 8",  "11 9",  "11 10", "11 11", "11 12",
      "11 13", "11 14", "12 1",  "12 2",  "12 3",  "12 4",  "12 5",  "12 6",
      "12 7",  "12 8",  "12 9",  "12 10", "12 11", "12 12", "12 13", "12 14",
      "13 1",  "13 2",  "13 3",  "13 4",  "13 5",  "13 6",  "13 7",  "13 8",
      "13 9",  "13 10", "13 11", "13 12", "13 13", "13 14", "14 1",  "14 2",
      "14 3",  "14 4",  "14 5",  "14 6",  "14 7",  "14 8",  "14 9",  "14 10",
      "14 11", "14 12", "14 13", "14 14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 9") {
  string query =
      "variable variable1, variable2;\n"
      "Select <variable1, variable2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"if if",
                                    "if if2",
                                    "if line1",
                                    "if line10",
                                    "if line11",
                                    "if line12",
                                    "if line13",
                                    "if line14",
                                    "if line3",
                                    "if line4",
                                    "if line5",
                                    "if line6",
                                    "if line7",
                                    "if line8",
                                    "if line9",
                                    "if variable",
                                    "if variable2",
                                    "if while2",
                                    "if2 if",
                                    "if2 if2",
                                    "if2 line1",
                                    "if2 line10",
                                    "if2 line11",
                                    "if2 line12",
                                    "if2 line13",
                                    "if2 line14",
                                    "if2 line3",
                                    "if2 line4",
                                    "if2 line5",
                                    "if2 line6",
                                    "if2 line7",
                                    "if2 line8",
                                    "if2 line9",
                                    "if2 variable",
                                    "if2 variable2",
                                    "if2 while2",
                                    "line1 if",
                                    "line1 if2",
                                    "line1 line1",
                                    "line1 line10",
                                    "line1 line11",
                                    "line1 line12",
                                    "line1 line13",
                                    "line1 line14",
                                    "line1 line3",
                                    "line1 line4",
                                    "line1 line5",
                                    "line1 line6",
                                    "line1 line7",
                                    "line1 line8",
                                    "line1 line9",
                                    "line1 variable",
                                    "line1 variable2",
                                    "line1 while2",
                                    "line10 if",
                                    "line10 if2",
                                    "line10 line1",
                                    "line10 line10",
                                    "line10 line11",
                                    "line10 line12",
                                    "line10 line13",
                                    "line10 line14",
                                    "line10 line3",
                                    "line10 line4",
                                    "line10 line5",
                                    "line10 line6",
                                    "line10 line7",
                                    "line10 line8",
                                    "line10 line9",
                                    "line10 variable",
                                    "line10 variable2",
                                    "line10 while2",
                                    "line11 if",
                                    "line11 if2",
                                    "line11 line1",
                                    "line11 line10",
                                    "line11 line11",
                                    "line11 line12",
                                    "line11 line13",
                                    "line11 line14",
                                    "line11 line3",
                                    "line11 line4",
                                    "line11 line5",
                                    "line11 line6",
                                    "line11 line7",
                                    "line11 line8",
                                    "line11 line9",
                                    "line11 variable",
                                    "line11 variable2",
                                    "line11 while2",
                                    "line12 if",
                                    "line12 if2",
                                    "line12 line1",
                                    "line12 line10",
                                    "line12 line11",
                                    "line12 line12",
                                    "line12 line13",
                                    "line12 line14",
                                    "line12 line3",
                                    "line12 line4",
                                    "line12 line5",
                                    "line12 line6",
                                    "line12 line7",
                                    "line12 line8",
                                    "line12 line9",
                                    "line12 variable",
                                    "line12 variable2",
                                    "line12 while2",
                                    "line13 if",
                                    "line13 if2",
                                    "line13 line1",
                                    "line13 line10",
                                    "line13 line11",
                                    "line13 line12",
                                    "line13 line13",
                                    "line13 line14",
                                    "line13 line3",
                                    "line13 line4",
                                    "line13 line5",
                                    "line13 line6",
                                    "line13 line7",
                                    "line13 line8",
                                    "line13 line9",
                                    "line13 variable",
                                    "line13 variable2",
                                    "line13 while2",
                                    "line14 if",
                                    "line14 if2",
                                    "line14 line1",
                                    "line14 line10",
                                    "line14 line11",
                                    "line14 line12",
                                    "line14 line13",
                                    "line14 line14",
                                    "line14 line3",
                                    "line14 line4",
                                    "line14 line5",
                                    "line14 line6",
                                    "line14 line7",
                                    "line14 line8",
                                    "line14 line9",
                                    "line14 variable",
                                    "line14 variable2",
                                    "line14 while2",
                                    "line3 if",
                                    "line3 if2",
                                    "line3 line1",
                                    "line3 line10",
                                    "line3 line11",
                                    "line3 line12",
                                    "line3 line13",
                                    "line3 line14",
                                    "line3 line3",
                                    "line3 line4",
                                    "line3 line5",
                                    "line3 line6",
                                    "line3 line7",
                                    "line3 line8",
                                    "line3 line9",
                                    "line3 variable",
                                    "line3 variable2",
                                    "line3 while2",
                                    "line4 if",
                                    "line4 if2",
                                    "line4 line1",
                                    "line4 line10",
                                    "line4 line11",
                                    "line4 line12",
                                    "line4 line13",
                                    "line4 line14",
                                    "line4 line3",
                                    "line4 line4",
                                    "line4 line5",
                                    "line4 line6",
                                    "line4 line7",
                                    "line4 line8",
                                    "line4 line9",
                                    "line4 variable",
                                    "line4 variable2",
                                    "line4 while2",
                                    "line5 if",
                                    "line5 if2",
                                    "line5 line1",
                                    "line5 line10",
                                    "line5 line11",
                                    "line5 line12",
                                    "line5 line13",
                                    "line5 line14",
                                    "line5 line3",
                                    "line5 line4",
                                    "line5 line5",
                                    "line5 line6",
                                    "line5 line7",
                                    "line5 line8",
                                    "line5 line9",
                                    "line5 variable",
                                    "line5 variable2",
                                    "line5 while2",
                                    "line6 if",
                                    "line6 if2",
                                    "line6 line1",
                                    "line6 line10",
                                    "line6 line11",
                                    "line6 line12",
                                    "line6 line13",
                                    "line6 line14",
                                    "line6 line3",
                                    "line6 line4",
                                    "line6 line5",
                                    "line6 line6",
                                    "line6 line7",
                                    "line6 line8",
                                    "line6 line9",
                                    "line6 variable",
                                    "line6 variable2",
                                    "line6 while2",
                                    "line7 if",
                                    "line7 if2",
                                    "line7 line1",
                                    "line7 line10",
                                    "line7 line11",
                                    "line7 line12",
                                    "line7 line13",
                                    "line7 line14",
                                    "line7 line3",
                                    "line7 line4",
                                    "line7 line5",
                                    "line7 line6",
                                    "line7 line7",
                                    "line7 line8",
                                    "line7 line9",
                                    "line7 variable",
                                    "line7 variable2",
                                    "line7 while2",
                                    "line8 if",
                                    "line8 if2",
                                    "line8 line1",
                                    "line8 line10",
                                    "line8 line11",
                                    "line8 line12",
                                    "line8 line13",
                                    "line8 line14",
                                    "line8 line3",
                                    "line8 line4",
                                    "line8 line5",
                                    "line8 line6",
                                    "line8 line7",
                                    "line8 line8",
                                    "line8 line9",
                                    "line8 variable",
                                    "line8 variable2",
                                    "line8 while2",
                                    "line9 if",
                                    "line9 if2",
                                    "line9 line1",
                                    "line9 line10",
                                    "line9 line11",
                                    "line9 line12",
                                    "line9 line13",
                                    "line9 line14",
                                    "line9 line3",
                                    "line9 line4",
                                    "line9 line5",
                                    "line9 line6",
                                    "line9 line7",
                                    "line9 line8",
                                    "line9 line9",
                                    "line9 variable",
                                    "line9 variable2",
                                    "line9 while2",
                                    "variable if",
                                    "variable if2",
                                    "variable line1",
                                    "variable line10",
                                    "variable line11",
                                    "variable line12",
                                    "variable line13",
                                    "variable line14",
                                    "variable line3",
                                    "variable line4",
                                    "variable line5",
                                    "variable line6",
                                    "variable line7",
                                    "variable line8",
                                    "variable line9",
                                    "variable variable",
                                    "variable variable2",
                                    "variable while2",
                                    "variable2 if",
                                    "variable2 if2",
                                    "variable2 line1",
                                    "variable2 line10",
                                    "variable2 line11",
                                    "variable2 line12",
                                    "variable2 line13",
                                    "variable2 line14",
                                    "variable2 line3",
                                    "variable2 line4",
                                    "variable2 line5",
                                    "variable2 line6",
                                    "variable2 line7",
                                    "variable2 line8",
                                    "variable2 line9",
                                    "variable2 variable",
                                    "variable2 variable2",
                                    "variable2 while2",
                                    "while2 if",
                                    "while2 if2",
                                    "while2 line1",
                                    "while2 line10",
                                    "while2 line11",
                                    "while2 line12",
                                    "while2 line13",
                                    "while2 line14",
                                    "while2 line3",
                                    "while2 line4",
                                    "while2 line5",
                                    "while2 line6",
                                    "while2 line7",
                                    "while2 line8",
                                    "while2 line9",
                                    "while2 variable",
                                    "while2 variable2",
                                    "while2 while2"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 10") {
  string query =
      "while while1, while2;\n"
      "Select <while1, while2>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4 4", "4 10", "10 4", "10 10"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 11") {
  string query =
      "read read1; call call1;\n"
      "Select <read1, call1>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1 2", "12 2", "13 2", "8 2"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 12") {
  string query =
      "assign assign; call call; constant constant; print print; procedure "
      "procedure;\n"
      "Select <assign, call, constant, print, procedure >";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "11 2 10 3 PotatoLine2", "11 2 10 3 procedure",   "11 2 10 9 PotatoLine2",
      "11 2 10 9 procedure",   "11 2 14 3 PotatoLine2", "11 2 14 3 procedure",
      "11 2 14 9 PotatoLine2", "11 2 14 9 procedure",   "11 2 5 3 PotatoLine2",
      "11 2 5 3 procedure",    "11 2 5 9 PotatoLine2",  "11 2 5 9 procedure",
      "14 2 10 3 PotatoLine2", "14 2 10 3 procedure",   "14 2 10 9 PotatoLine2",
      "14 2 10 9 procedure",   "14 2 14 3 PotatoLine2", "14 2 14 3 procedure",
      "14 2 14 9 PotatoLine2", "14 2 14 9 procedure",   "14 2 5 3 PotatoLine2",
      "14 2 5 3 procedure",    "14 2 5 9 PotatoLine2",  "14 2 5 9 procedure",
      "6 2 10 3 PotatoLine2",  "6 2 10 3 procedure",    "6 2 10 9 PotatoLine2",
      "6 2 10 9 procedure",    "6 2 14 3 PotatoLine2",  "6 2 14 3 procedure",
      "6 2 14 9 PotatoLine2",  "6 2 14 9 procedure",    "6 2 5 3 PotatoLine2",
      "6 2 5 3 procedure",     "6 2 5 9 PotatoLine2",   "6 2 5 9 procedure"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 13") {
  string query =
      "call call;\n"
      "Select <call, call.procName, call.stmt#>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2 PotatoLine2 2"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 14") {
  string query =
      "read read;\n"
      "Select <read, read.varName, read.stmt#>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"8 line8 8", "1 line1 1", "12 line12 12",
                                    "13 line13 13"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 15") {
  string query =
      "print print;\n"
      "Select <print, print.varName, print.stmt#>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"9 line9 9", "3 line3 3"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 16") {
  string query =
      "stmt stmt;\n"
      "Select <stmt, stmt.stmt#>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"11 11", "2 2",   "8 8",   "7 7",  "6 6",
                                    "5 5",   "4 4",   "3 3",   "9 9",  "1 1",
                                    "10 10", "12 12", "13 13", "14 14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 17") {
  string query =
      "stmt stmt;\n"
      "Select <stmt, stmt.varName, stmt.stmt#>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 18") {
  string query =
      "constant c;\n"
      "Select <c, c.value>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"10 10", "14 14", "5 5"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 19") {
  string query =
      "variable v;\n"
      "Select <v, v.varName>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "line10 line10", "line14 line14",      "line5 line5",   "line6 line6",
      "line4 line4",   "line3 line3",        "line8 line8",   "line7 line7",
      "line1 line1",   "line11 line11",      "if if",         "line13 line13",
      "if2 if2",       "variable variable",  "line12 line12", "line9 line9",
      "while2 while2", "variable2 variable2"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 20") {
  string query =
      "while c;\n"
      "Select <c, c.stmt#>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4 4", "10 10"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 21") {
  string query =
      "if if;\n"
      "Select <if, if.stmt#>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"5 5", "7 7"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 22") {
  string query =
      "assign if;\n"
      "Select <if, if.stmt#>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"6 6", "11 11", "14 14"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone2/SingleClauseTests/TupleSelect_queries.txt - 23") {
  string query =
      "procedure call;\n"
      "Select <call, call.procName>";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(selectTuplePatternSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"PotatoLine2 PotatoLine2",
                                    "procedure procedure"};
  REQUIRE(result == expected);
}
