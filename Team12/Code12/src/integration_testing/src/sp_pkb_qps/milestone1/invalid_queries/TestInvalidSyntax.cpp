#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "catch.hpp"
#include "pkb/facade/PKB.h"
#include "qps/QPS.h"
#include "sp/SourceProcessor.h"

using std::string, std::unordered_map, std::map, std::unordered_set, std::set,
    std::vector, std::pair;

string sourceInvalidSyntax =
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
    "../../Tests12/Milestone1/InvalidQueries/SyntacticallyInvalid_queries.txt "
    "- 1") {
  string query =
      "stmt s;\n"
      "Select s such that Follows *(_, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSyntax, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SyntaxError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone1/InvalidQueries/SyntacticallyInvalid_queries.txt "
    "- 2") {
  string query =
      "stmt s;\n"
      "Select s such that Parent *(_, _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSyntax, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SyntaxError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone1/InvalidQueries/SyntacticallyInvalid_queries.txt "
    "- 3") {
  string query =
      "assign a;\n"
      "Select a such that pattern a(\"1\", _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSyntax, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SyntaxError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone1/InvalidQueries/SyntacticallyInvalid_queries.txt "
    "- 4") {
  string query =
      "assign a;\n"
      "Select a such that pattern a(\"1a\", _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSyntax, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SyntaxError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone1/InvalidQueries/SyntacticallyInvalid_queries.txt "
    "- 5") {
  string query =
      "assign a;\n"
      "Select a such that pattern a(\"_\", _)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSyntax, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SyntaxError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone1/InvalidQueries/SyntacticallyInvalid_queries.txt "
    "- 6") {
  string query =
      "assign a;\n"
      "Select a such that pattern a(_, _\"+y\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSyntax, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SyntaxError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone1/InvalidQueries/SyntacticallyInvalid_queries.txt "
    "- 7") {
  string query =
      "assign a;\n"
      "Select a such that pattern a(_, _\"x+\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSyntax, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SyntaxError"};
  REQUIRE(result == expected);
}

TEST_CASE(
    "SP-PKB-QPS "
    "../../Tests12/Milestone1/InvalidQueries/SyntacticallyInvalid_queries.txt "
    "- 8") {
  string query =
      "assign a;\n"
      "Select a such that pattern a(_, _\"01\"_)";
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(sourceInvalidSyntax, pkb.getWriter());
  QPS qps(pkb.getReader());
  auto result = qps.processQueryString(query);
  set<string> expected = {"SyntaxError"};
  REQUIRE(result == expected);
}
