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

string basicSource =
    "procedure procedure {  read read;\n"
    "  print print;\n"
    "  while ((!(while != while))||(while<=while)) {\n"
    "    if ((if == if) && ( ! (if >= if))) then{\n"
    "        assign = variable + 5;\n"
    "        if ((if2 < if2) && ( ! (if2 > if2))) then{\n"
    "                read read2;\n"
    "                print print2;\n"
    "                while ((while2 > while2)&&(!(while2<while2))) {\n"
    "                    assign2 = variable2 + 10;\n"
    "                }} else {read read3;\n"
    "             }        }else{read read4;}}}";

TEST_CASE("SP-PKB-QPS integration - 1") {
  string query =
      "read read;\n"
      "Select read";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "7", "11", "12"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 2") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign, assign2 ; variable variable, variable2     ;\n"
      "Select read2";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "7", "11", "12"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 3") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ;\n"
      "Select print";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2", "8"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 4") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ;\n"
      "Select print2";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"2", "8"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 5") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ;\n"
      "Select while";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"3", "9"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 6") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ;\n"
      "Select while2";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"3", "9"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 7") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ;\n"
      "Select if";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "6"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 8") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ;\n"
      "Select if2";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"4", "6"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 9") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ;\n"
      "Select assign";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"5", "10"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 10") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ;\n"
      "Select assign2";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"5", "10"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 11") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ; stmt "
      "stmt;stmt Select;\n"
      "Select variable";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "read",   "read2", "read3", "read4",  "print",   "print2",   "while",
      "while2", "if",    "if2",   "assign", "assign2", "variable", "variable2"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 12") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ; stmt "
      "stmt;stmt Select;\n"
      "Select variable2";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {
      "read",   "read2", "read3", "read4",  "print",   "print2",   "while",
      "while2", "if",    "if2",   "assign", "assign2", "variable", "variable2"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 13") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ; stmt "
      "stmt;stmt Select;\n"
      "Select stmt";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "2", "3", "4",  "5",  "6",
                                    "7", "8", "9", "10", "11", "12"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 14") {
  string query =
      "read read,read2; print print ,print2; while while, while2 ; if if, if2; "
      "assign assign ,assign2 ; variable variable, variable2     ; stmt "
      "stmt;stmt Select;\n"
      "Select Select";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"1", "2", "3", "4",  "5",  "6",
                                    "7", "8", "9", "10", "11", "12"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 15") {
  string query =
      "constant constant; constant pattern; read read,read2; print print "
      ",print2; while while, while2 ; if if, if2; assign assign ,assign2 ; "
      "variable variable, variable2     ; stmt stmt;stmt Select;\n"
      "Select constant";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"5", "10"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 16") {
  string query =
      "constant constant; constant pattern; read read,read2; print print "
      ",print2; while while, while2 ; if if, if2; assign assign ,assign2 ; "
      "variable variable, variable2     ; stmt stmt;stmt Select;\n"
      "Select pattern";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());

  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"5", "10"};
  REQUIRE(result == expected);
}

TEST_CASE("SP-PKB-QPS integration - 17") {
  string query =
      "read read,read2;procedure constant;print print ,print2; while while, "
      "while2 ; if if, if2; assign assign ,assign2 ; variable variable, "
      "variable2     ; stmt stmt;stmt Select;\n"
      "Select constant";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(basicSource, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  unordered_set<string> expected = {"procedure"};
  REQUIRE(result == expected);
}
