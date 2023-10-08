#include <catch.hpp>
#include "sp/SourceProcessor.h"
#include "pkb/facade/PKB.h"
#include "qps/QPS.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <set>

using std::string, std::unordered_map, std::map, std::unordered_set, std::set,
    std::vector, std::pair;

string sourceInvalidSemantics =
    "procedure procedure {  read read;"
    "  print print;"
    "  while ((!(while != while))||(while<=while)) {"
    "    if ((if == if) && ( ! (if >= if))) then{"
    "        assign = variable + 5;"
    "        if ((if2 < if2) && ( ! (if2 > if2))) then{"
    "                read read2;"
    "                print print2;"
    "                while ((while2 > while2)&&(!(while2<while2))) {"
    "                    assign2 = variable2 + 10;"
    "                }} else {read read3;"
    "             }        }else{read read4;}}}";

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone1/InvalidQueries/SemanticallyInvalid_queries.txt - "
    "1") {
  string query = "\nSelect s\n";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSemantics, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone1/InvalidQueries/SemanticallyInvalid_queries.txt - "
    "2") {
  string query =
      "assign aSsign;\n"
      "Select assign";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSemantics, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone1/InvalidQueries/SemanticallyInvalid_queries.txt - "
    "3") {
  string query =
      "assign a;\n"
      "Select a pattern a(a,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSemantics, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone1/InvalidQueries/SemanticallyInvalid_queries.txt - "
    "4") {
  string query =
      "assign a; constant c;\n"
      "Select a  pattern a(c,_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSemantics, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SemanticError"};
  REQUIRE(result == expected);
}
