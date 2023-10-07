#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "pkb/facade/PKB.h"
#include "sp/SourceProcessor.h"

using std::string, std::unordered_map, std::map, std::unordered_set, std::set,
    std::vector, std::pair;

void validateEntities(PKBReader &reader, const set<string> &expectedVars,
                      const set<string> &expectedConstants,
                      const set<string> &expectedProcedures,
                      const set<string> &expectedReadStmts,
                      const set<string> &expectedPrintStmts,
                      const set<string> &expectedAssignStmts,
                      const set<string> &expectedCallStmts,
                      const set<string> &expectedWhileStmts,
                      const set<string> &expectedIfStmts) {
  REQUIRE(reader.getAllVariables() == expectedVars);
  REQUIRE(reader.getAllConstants() == expectedConstants);
  REQUIRE(reader.getAllProcedures() == expectedProcedures);
  REQUIRE(reader.getStatement(StmtType::READ) == expectedReadStmts);
  REQUIRE(reader.getStatement(StmtType::PRINT) == expectedPrintStmts);
  REQUIRE(reader.getStatement(StmtType::ASSIGN) == expectedAssignStmts);
  REQUIRE(reader.getStatement(StmtType::CALL) == expectedCallStmts);
  REQUIRE(reader.getStatement(StmtType::WHILE) == expectedWhileStmts);
  REQUIRE(reader.getStatement(StmtType::IF) == expectedIfStmts);
}

void validateFollows(PKBReader &reader,
                     vector<pair<string, string>> &expectedFollowsPairs,
                     vector<pair<string, string>> &expectedFollowsStarPairs) {
  std::sort(expectedFollowsPairs.begin(), expectedFollowsPairs.end());
  std::sort(expectedFollowsStarPairs.begin(), expectedFollowsStarPairs.end());
  vector<pair<string, string>> actualFollowsPairs =
      reader.getFollowsPairs(StmtType::STMT, StmtType::STMT);
  vector<pair<string, string>> actualFollowsStarPairs =
      reader.getFollowsStarPairs(StmtType::STMT, StmtType::STMT);
  std::sort(actualFollowsPairs.begin(), actualFollowsPairs.end());
  std::sort(actualFollowsStarPairs.begin(), actualFollowsStarPairs.end());
  REQUIRE(actualFollowsPairs == expectedFollowsPairs);
  REQUIRE(actualFollowsStarPairs == expectedFollowsStarPairs);
}

void validateParents(
    PKBReader &reader, vector<pair<string, string>> &expectedParentChildPairs,
    vector<pair<string, string>> &expectedParentChildStarPairs) {
  std::sort(expectedParentChildPairs.begin(), expectedParentChildPairs.end());
  std::sort(expectedParentChildStarPairs.begin(),
            expectedParentChildStarPairs.end());
  vector<pair<string, string>> actualParentChildPairs =
      reader.getParentChildPairs(StmtType::STMT, StmtType::STMT);
  vector<pair<string, string>> actualParentChildStarPairs =
      reader.getParentChildStarPairs(StmtType::STMT, StmtType::STMT);
  std::sort(actualParentChildPairs.begin(), actualParentChildPairs.end());
  std::sort(actualParentChildStarPairs.begin(),
            actualParentChildStarPairs.end());
  REQUIRE(actualParentChildPairs == expectedParentChildPairs);
  REQUIRE(actualParentChildStarPairs == expectedParentChildStarPairs);
}

void validateModifies(PKBReader &reader,
                      vector<pair<string, string>> &expectedModifiesPairs) {
  std::sort(expectedModifiesPairs.begin(), expectedModifiesPairs.end());
  vector<pair<string, string>> actual =
      reader.getAllModifiedVariables(StmtType::STMT);
  std::sort(actual.begin(), actual.end());
  REQUIRE(actual == expectedModifiesPairs);
}

void validateUses(PKBReader &reader,
                  vector<pair<string, string>> &expectedUsesPairs) {
  std::sort(expectedUsesPairs.begin(), expectedUsesPairs.end());
  vector<pair<string, string>> actual =
      reader.getAllUsedVariables(StmtType::STMT);
  std::sort(actual.begin(), actual.end());
  REQUIRE(actual == expectedUsesPairs);
}

TEST_CASE("SP-PKB integration - Non-nesting statements") {
  string input =
      "procedure simple {"
      "read num1;"     // 1
      "print num2;"    // 2
      "x = num1 + 1;"  // 3
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader &reader = pkb.getReader();
  // check
  set<string> expectedVars = {"num1", "num2", "x"};
  set<string> expectedConstants = {"1"};
  set<string> expectedProcedures = {"simple"};
  set<string> expectedReadStmts = {"1"};
  set<string> expectedPrintStmts = {"2"};
  set<string> expectedAssignStmts = {"3"};
  set<string> expectedCallStmts = {};
  set<string> expectedWhileStmts = {};
  set<string> expectedIfStmts = {};
  vector<pair<string, string>> expectedFollowsPairs = {{"1", "2"}, {"2", "3"}};
  vector<pair<string, string>> expectedFollowsStarPairs = {
      {"1", "2"}, {"1", "3"}, {"2", "3"}};
  vector<pair<string, string>> expectedParentChildPairs = {};
  vector<pair<string, string>> expectedParentChildStarPairs = {};
  vector<pair<string, string>> expectedModifiesPairs = {{"1", "num1"},
                                                        {"3", "x"}};
  vector<pair<string, string>> expectedUsesPairs = {{"2", "num2"},
                                                    {"3", "num1"}};
  vector<string> expectedAssignPatternStmts = {"3"};
  validateEntities(reader, expectedVars, expectedConstants, expectedProcedures,
                   expectedReadStmts, expectedPrintStmts, expectedAssignStmts,
                   expectedCallStmts, expectedWhileStmts, expectedIfStmts);
  validateFollows(reader, expectedFollowsPairs, expectedFollowsStarPairs);
  validateParents(reader, expectedParentChildPairs,
                  expectedParentChildStarPairs);
  validateModifies(reader, expectedModifiesPairs);
  validateUses(reader, expectedUsesPairs);
  REQUIRE(reader.getExactAssignPattern("_", "_", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getExactAssignPattern("x", " num1 1 + ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getExactAssignPattern("x", " num1 2 + ", false).empty());
  REQUIRE(reader.getExactAssignPattern("num1", " num1 1 + ", false).empty());
  REQUIRE(reader.getPartialAssignPattern("_", "_", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " num1 1 + ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " num1 ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " 1 ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " num1 2 + ", false).empty());
  REQUIRE(reader.getPartialAssignPattern("num1", "n um1 1 + ", false).empty());
}

TEST_CASE("SP-PKB integration - if statement") {
  string input =
      "procedure simple {"
      "read y;"                  // 1
      "print x;"                 // 2
      "if (num1 < num2) then {"  // 3
      "print z;"                 // 4
      "} else {"
      "x = y + 1;"  // 5
      "}"
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader &reader = pkb.getReader();
  // check
  set<string> expectedVars = {"y", "x", "num1", "num2", "z"};
  set<string> expectedConstants = {"1"};
  set<string> expectedProcedures = {"simple"};
  set<string> expectedReadStmts = {"1"};
  set<string> expectedPrintStmts = {"2", "4"};
  set<string> expectedAssignStmts = {"5"};
  set<string> expectedCallStmts = {};
  set<string> expectedWhileStmts = {};
  set<string> expectedIfStmts = {"3"};
  vector<pair<string, string>> expectedFollowsPairs = {{"1", "2"}, {"2", "3"}};
  vector<pair<string, string>> expectedFollowsStarPairs = {
      {"1", "2"}, {"1", "3"}, {"2", "3"}};
  vector<pair<string, string>> expectedParentChildPairs = {{"3", "4"},
                                                           {"3", "5"}};
  vector<pair<string, string>> expectedParentChildStarPairs = {{"3", "4"},
                                                               {"3", "5"}};
  vector<pair<string, string>> expectedModifiesPairs = {
      {"5", "x"}, {"3", "x"}, {"1", "y"}};
  vector<pair<string, string>> expectedUsesPairs = {
      {"2", "x"}, {"3", "num1"}, {"3", "num2"}, {"5", "y"},
      {"3", "y"}, {"4", "z"},    {"3", "z"}};
  vector<string> expectedAssignPatternStmts = {"5"};
  validateEntities(reader, expectedVars, expectedConstants, expectedProcedures,
                   expectedReadStmts, expectedPrintStmts, expectedAssignStmts,
                   expectedCallStmts, expectedWhileStmts, expectedIfStmts);
  validateFollows(reader, expectedFollowsPairs, expectedFollowsStarPairs);
  validateParents(reader, expectedParentChildPairs,
                  expectedParentChildStarPairs);
  validateModifies(reader, expectedModifiesPairs);
  validateUses(reader, expectedUsesPairs);
  REQUIRE(reader.getExactAssignPattern("_", "_", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getExactAssignPattern("x", " y 1 + ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getExactAssignPattern("x", " y 2 + ", false).empty());
  REQUIRE(reader.getExactAssignPattern("y", " y 1 + ", false).empty());
  REQUIRE(reader.getPartialAssignPattern("_", "_", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " y 1 + ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " y ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " 1 ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " y 2 + ", false).empty());
  REQUIRE(reader.getPartialAssignPattern("y", " y 1 + ", false).empty());
}

TEST_CASE("SP-PKB integration - if in while statements") {
  string input =
      "procedure simple {"
      "    read x;"                  // 1
      "    read y;"                  // 2
      "    while (x < y) {"          // 3
      "        if (x == y) then {"   // 4
      "            x = y + 1;"       // 5
      "        } else { print w; }"  // 6
      "        print z;"             // 7
      "    }"
      "    read num1;"  // 8
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader &reader = pkb.getReader();
  // check
  set<string> expectedVars = {"x", "y", "w", "z", "num1"};
  set<string> expectedConstants = {"1"};
  set<string> expectedProcedures = {"simple"};
  set<string> expectedReadStmts = {"1", "2", "8"};
  set<string> expectedPrintStmts = {"6", "7"};
  set<string> expectedAssignStmts = {"5"};
  set<string> expectedCallStmts = {};
  set<string> expectedWhileStmts = {"3"};
  set<string> expectedIfStmts = {"4"};
  vector<pair<string, string>> expectedFollowsPairs = {
      {"1", "2"}, {"2", "3"}, {"3", "8"}, {"4", "7"}};
  vector<pair<string, string>> expectedFollowsStarPairs = {
      {"1", "2"}, {"1", "3"}, {"2", "3"}, {"1", "8"},
      {"2", "8"}, {"3", "8"}, {"4", "7"}};
  vector<pair<string, string>> expectedParentChildPairs = {
      {"3", "4"}, {"3", "7"}, {"4", "5"}, {"4", "6"}};
  vector<pair<string, string>> expectedParentChildStarPairs = {
      {"3", "4"}, {"3", "7"}, {"3", "5"}, {"3", "6"}, {"4", "5"}, {"4", "6"}};
  vector<pair<string, string>> expectedModifiesPairs = {
      {"1", "x"}, {"3", "x"}, {"4", "x"}, {"5", "x"}, {"2", "y"}, {"8", "num1"},
  };
  vector<pair<string, string>> expectedUsesPairs = {
      {"3", "x"}, {"3", "y"}, {"4", "x"}, {"4", "y"}, {"5", "y"},
      {"3", "w"}, {"4", "w"}, {"6", "w"}, {"3", "z"}, {"7", "z"}};
  vector<string> expectedAssignPatternStmts = {"5"};
  validateEntities(reader, expectedVars, expectedConstants, expectedProcedures,
                   expectedReadStmts, expectedPrintStmts, expectedAssignStmts,
                   expectedCallStmts, expectedWhileStmts, expectedIfStmts);
  validateFollows(reader, expectedFollowsPairs, expectedFollowsStarPairs);
  validateParents(reader, expectedParentChildPairs,
                  expectedParentChildStarPairs);
  validateModifies(reader, expectedModifiesPairs);
  validateUses(reader, expectedUsesPairs);
  REQUIRE(reader.getExactAssignPattern("_", "_", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getExactAssignPattern("x", " y 1 + ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getExactAssignPattern("x", " y 2 + ", false).empty());
  REQUIRE(reader.getExactAssignPattern("y", " y 1 + ", false).empty());
  REQUIRE(reader.getPartialAssignPattern("_", "_", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " y 1 + ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " y ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " 1 ", false) ==
          expectedAssignPatternStmts);
  REQUIRE(reader.getPartialAssignPattern("x", " y 2 + ", false).empty());
  REQUIRE(reader.getPartialAssignPattern("y", " y 1 + ", false).empty());
}

TEST_CASE("SP-PKB integration - 3 if statements") {
  string input =
      "procedure multipleIf {"
      "   read v;"                          // 1
      "   read w;"                          // 2
      "   if (v == 0) then {"               // 3
      "       read x;"                      // 4
      "       if (w != v) then {"           // 5
      "           read y;"                  // 6
      "           if (x > (y - 1)) then {"  // 7
      "               read z;"              // 8
      "           } else { print x; }"      // 9
      "       } else { print z; }"          // 10
      "   } else { print v; }"              // 11
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader &reader = pkb.getReader();
  // check
  set<string> expectedVars = {"v", "w", "x", "y", "z"};
  set<string> expectedConstants = {"0", "1"};
  set<string> expectedProcedures = {"multipleIf"};
  set<string> expectedReadStmts = {"1", "2", "4", "6", "8"};
  set<string> expectedPrintStmts = {"9", "10", "11"};
  set<string> expectedAssignStmts = {};
  set<string> expectedCallStmts = {};
  set<string> expectedWhileStmts = {};
  set<string> expectedIfStmts = {"3", "5", "7"};
  vector<pair<string, string>> expectedFollowsPairs = {
      {"1", "2"}, {"2", "3"}, {"4", "5"}, {"6", "7"}};
  vector<pair<string, string>> expectedFollowsStarPairs = {
      {"1", "2"}, {"1", "3"}, {"2", "3"}, {"4", "5"}, {"6", "7"}};
  vector<pair<string, string>> expectedParentChildPairs = {
      {"3", "4"}, {"3", "5"},  {"3", "11"}, {"5", "6"},
      {"5", "7"}, {"5", "10"}, {"7", "8"},  {"7", "9"}};
  vector<pair<string, string>> expectedParentChildStarPairs = {
      {"3", "4"}, {"3", "5"},  {"3", "6"},  {"3", "7"}, {"3", "8"},
      {"3", "9"}, {"3", "10"}, {"3", "11"}, {"5", "6"}, {"5", "7"},
      {"5", "8"}, {"5", "9"},  {"5", "10"}, {"7", "8"}, {"7", "9"}};
  vector<pair<string, string>> expectedModifiesPairs = {
      {"1", "v"}, {"2", "w"}, {"3", "x"}, {"4", "x"}, {"3", "y"}, {"5", "y"},
      {"6", "y"}, {"3", "z"}, {"5", "z"}, {"7", "z"}, {"8", "z"}};
  vector<pair<string, string>> expectedUsesPairs = {
      {"3", "v"}, {"5", "v"}, {"11", "v"}, {"3", "w"}, {"5", "w"},
      {"3", "x"}, {"5", "x"}, {"7", "x"},  {"9", "x"}, {"3", "y"},
      {"5", "y"}, {"7", "y"}, {"3", "z"},  {"5", "z"}, {"10", "z"},
  };
  validateEntities(reader, expectedVars, expectedConstants, expectedProcedures,
                   expectedReadStmts, expectedPrintStmts, expectedAssignStmts,
                   expectedCallStmts, expectedWhileStmts, expectedIfStmts);
  validateFollows(reader, expectedFollowsPairs, expectedFollowsStarPairs);
  validateParents(reader, expectedParentChildPairs,
                  expectedParentChildStarPairs);
  validateModifies(reader, expectedModifiesPairs);
  validateUses(reader, expectedUsesPairs);
  REQUIRE(reader.getExactAssignPattern("_", "_", false).empty());
  REQUIRE(reader.getPartialAssignPattern("_", "_", false).empty());
}

TEST_CASE("SP-PKB integration - 3 while statements") {
  string input =
      "procedure multipleWhiles {"
      "   read v;"                        // 1
      "   read w;"                        // 2
      "   while (v == 0) {"               // 3
      "       read x;"                    // 4
      "       while (w != v) {"           // 5
      "           read y;"                // 6
      "           while (x > (y - 1)) {"  // 7
      "               read z;"            // 8
      "           }"
      "       }"
      "   }"
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader &reader = pkb.getReader();
  // check
  set<string> expectedVars = {"v", "w", "x", "y", "z"};
  set<string> expectedConstants = {"0", "1"};
  set<string> expectedProcedures = {"multipleWhiles"};
  set<string> expectedReadStmts = {"1", "2", "4", "6", "8"};
  set<string> expectedPrintStmts = {};
  set<string> expectedAssignStmts = {};
  set<string> expectedCallStmts = {};
  set<string> expectedWhileStmts = {"3", "5", "7"};
  set<string> expectedIfStmts = {};
  vector<pair<string, string>> expectedFollowsPairs = {
      {"1", "2"}, {"2", "3"}, {"4", "5"}, {"6", "7"}};
  vector<pair<string, string>> expectedFollowsStarPairs = {
      {"1", "2"}, {"1", "3"}, {"2", "3"}, {"4", "5"}, {"6", "7"}};
  vector<pair<string, string>> expectedParentChildPairs = {
      {"3", "4"}, {"3", "5"}, {"5", "6"}, {"5", "7"}, {"7", "8"}};
  vector<pair<string, string>> expectedParentChildStarPairs = {
      {"3", "4"}, {"3", "5"}, {"3", "6"}, {"3", "7"}, {"3", "8"},
      {"5", "6"}, {"5", "7"}, {"5", "8"}, {"7", "8"}};
  vector<pair<string, string>> expectedModifiesPairs = {
      {"1", "v"}, {"2", "w"}, {"3", "x"}, {"4", "x"}, {"3", "y"}, {"5", "y"},
      {"6", "y"}, {"3", "z"}, {"5", "z"}, {"7", "z"}, {"8", "z"}};
  vector<pair<string, string>> expectedUsesPairs = {
      {"3", "v"}, {"5", "v"}, {"5", "w"}, {"3", "w"}, {"7", "x"},
      {"5", "x"}, {"3", "x"}, {"7", "y"}, {"5", "y"}, {"3", "y"},
  };
  validateEntities(reader, expectedVars, expectedConstants, expectedProcedures,
                   expectedReadStmts, expectedPrintStmts, expectedAssignStmts,
                   expectedCallStmts, expectedWhileStmts, expectedIfStmts);
  validateFollows(reader, expectedFollowsPairs, expectedFollowsStarPairs);
  validateParents(reader, expectedParentChildPairs,
                  expectedParentChildStarPairs);
  validateModifies(reader, expectedModifiesPairs);
  validateUses(reader, expectedUsesPairs);
  REQUIRE(reader.getExactAssignPattern("_", "_", false).empty());
  REQUIRE(reader.getPartialAssignPattern("_", "_", false).empty());
}

TEST_CASE("SP-PKB integration - sequential if pattern") {
  string input =
      "procedure multipleIf {"
      "   read i;"              // 1
      "   if (i > 0) then {"    // 2
      "       read j;"          // 3
      "   } else { read i; }"   // 4
      "   read k;"              // 5
      "   if (k <= i) then {"   // 6
      "       read l;"          // 7
      "   } else { print i; }"  // 8
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader &reader = pkb.getReader();
  set<string> expectedVars = {"i", "j", "k", "l"};
  set<string> expectedConstants = {"0"};
  set<string> expectedProcedures = {"multipleIf"};
  set<string> expectedReadStmts = {"1", "3", "4", "5", "7"};
  set<string> expectedPrintStmts = {"8"};
  set<string> expectedAssignStmts = {};
  set<string> expectedCallStmts = {};
  set<string> expectedWhileStmts = {};
  set<string> expectedIfStmts = {"2", "6"};
  vector<pair<string, string>> expectedFollowsPairs = {
      {"1", "2"}, {"2", "5"}, {"5", "6"}};
  vector<pair<string, string>> expectedFollowsStarPairs = {
      {"1", "2"}, {"1", "5"}, {"1", "6"}, {"2", "5"}, {"2", "6"}, {"5", "6"}};
  vector<pair<string, string>> expectedParentChildPairs = {
      {"2", "3"}, {"2", "4"}, {"6", "7"}, {"6", "8"}};
  vector<pair<string, string>> expectedParentChildStarPairs = {
      {"2", "3"}, {"2", "4"}, {"6", "7"}, {"6", "8"}};
  vector<pair<string, string>> expectedModifiesPairs = {
      {"1", "i"}, {"2", "i"}, {"4", "i"}, {"3", "j"},
      {"2", "j"}, {"5", "k"}, {"7", "l"}, {"6", "l"}};
  vector<pair<string, string>> expectedUsesPairs = {
      {"2", "i"}, {"6", "i"}, {"8", "i"}, {"6", "k"}};
  validateEntities(reader, expectedVars, expectedConstants, expectedProcedures,
                   expectedReadStmts, expectedPrintStmts, expectedAssignStmts,
                   expectedCallStmts, expectedWhileStmts, expectedIfStmts);
  validateFollows(reader, expectedFollowsPairs, expectedFollowsStarPairs);
  validateParents(reader, expectedParentChildPairs,
                  expectedParentChildStarPairs);
  validateModifies(reader, expectedModifiesPairs);
  validateUses(reader, expectedUsesPairs);
  REQUIRE(reader.getExactAssignPattern("_", "_", false).empty());
  REQUIRE(reader.getPartialAssignPattern("_", "_", false).empty());
}

TEST_CASE("SP-PKB integration - sequential while statements") {
  string input =
      "procedure multipleWhile {"
      "   read i;"          // 1
      "   while (i > 0) {"  // 2
      "       read j;"      // 3
      "   }"
      "   read k;"           // 4
      "   while (k <= i) {"  // 5
      "       read l;"       // 6
      "   }"
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader &reader = pkb.getReader();
  set<string> expectedVars = {"i", "j", "k", "l"};
  set<string> expectedConstants = {"0"};
  set<string> expectedProcedures = {"multipleWhile"};
  set<string> expectedReadStmts = {"1", "3", "4", "6"};
  set<string> expectedPrintStmts = {};
  set<string> expectedAssignStmts = {};
  set<string> expectedCallStmts = {};
  set<string> expectedWhileStmts = {"2", "5"};
  set<string> expectedIfStmts = {};
  vector<pair<string, string>> expectedFollowsPairs = {
      {"1", "2"}, {"2", "4"}, {"4", "5"}};
  vector<pair<string, string>> expectedFollowsStarPairs = {
      {"1", "2"}, {"1", "4"}, {"1", "5"}, {"2", "4"}, {"2", "5"}, {"4", "5"}};
  vector<pair<string, string>> expectedParentChildPairs = {{"2", "3"},
                                                           {"5", "6"}};
  vector<pair<string, string>> expectedParentChildStarPairs = {{"2", "3"},
                                                               {"5", "6"}};
  vector<pair<string, string>> expectedModifiesPairs = {
      {"1", "i"}, {"2", "j"}, {"3", "j"}, {"4", "k"}, {"6", "l"}, {"5", "l"}};
  vector<pair<string, string>> expectedUsesPairs = {
      {"2", "i"}, {"5", "i"}, {"5", "k"}};
  validateEntities(reader, expectedVars, expectedConstants, expectedProcedures,
                   expectedReadStmts, expectedPrintStmts, expectedAssignStmts,
                   expectedCallStmts, expectedWhileStmts, expectedIfStmts);
  validateFollows(reader, expectedFollowsPairs, expectedFollowsStarPairs);
  validateParents(reader, expectedParentChildPairs,
                  expectedParentChildStarPairs);
  validateModifies(reader, expectedModifiesPairs);
  validateUses(reader, expectedUsesPairs);
  REQUIRE(reader.getExactAssignPattern("_", "_", false).empty());
  REQUIRE(reader.getPartialAssignPattern("_", "_", false).empty());
}

TEST_CASE(
    "SP-PKB integration - multiple control variables in while statements") {
  string input =
      "procedure complexConditions {"
      "   read p;"
      "   read q;"
      "   while ((p + q * 2) == (x - y % 3)) {"
      "       read r;"
      "   }"
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader &reader = pkb.getReader();
  set<string> expectedVars = {"p", "q", "r", "x", "y"};
  set<string> expectedConstants = {"2", "3"};
  set<string> expectedProcedures = {"complexConditions"};
  set<string> expectedReadStmts = {"1", "2", "4"};
  set<string> expectedPrintStmts = {};
  set<string> expectedAssignStmts = {};
  set<string> expectedCallStmts = {};
  set<string> expectedWhileStmts = {"3"};
  set<string> expectedIfStmts = {};
  vector<pair<string, string>> expectedFollowsPairs = {{"1", "2"}, {"2", "3"}};
  vector<pair<string, string>> expectedFollowsStarPairs = {
      {"1", "2"}, {"1", "3"}, {"2", "3"}};
  vector<pair<string, string>> expectedParentChildPairs = {{"3", "4"}};
  vector<pair<string, string>> expectedParentChildStarPairs = {{"3", "4"}};
  vector<pair<string, string>> expectedModifiesPairs = {
      {"1", "p"}, {"2", "q"}, {"4", "r"}, {"3", "r"}};
  vector<pair<string, string>> expectedUsesPairs = {
      {"3", "p"}, {"3", "q"}, {"3", "x"}, {"3", "y"}};
  validateEntities(reader, expectedVars, expectedConstants, expectedProcedures,
                   expectedReadStmts, expectedPrintStmts, expectedAssignStmts,
                   expectedCallStmts, expectedWhileStmts, expectedIfStmts);
  validateFollows(reader, expectedFollowsPairs, expectedFollowsStarPairs);
  validateParents(reader, expectedParentChildPairs,
                  expectedParentChildStarPairs);
  validateModifies(reader, expectedModifiesPairs);
  validateUses(reader, expectedUsesPairs);
  REQUIRE(reader.getExactAssignPattern("_", "_", false).empty());
  REQUIRE(reader.getPartialAssignPattern("_", "_", false).empty());
}

TEST_CASE("SP-PKB integration - multiple control variables in if statements") {
  string input =
      "procedure complexConditions {"
      "   read p;"                                 // 1
      "   read q;"                                 // 2
      "   if ((p + q * 2) == (x - y % 3)) then {"  // 3
      "       read r;"                             // 4
      "   } else { print p; }"                     // 5
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader &reader = pkb.getReader();
  set<string> expectedVars = {"p", "q", "r", "x", "y"};
  set<string> expectedConstants = {"2", "3"};
  set<string> expectedProcedures = {"complexConditions"};
  set<string> expectedReadStmts = {"1", "2", "4"};
  set<string> expectedPrintStmts = {"5"};
  set<string> expectedAssignStmts = {};
  set<string> expectedCallStmts = {};
  set<string> expectedWhileStmts = {};
  set<string> expectedIfStmts = {"3"};
  vector<pair<string, string>> expectedFollowsPairs = {{"1", "2"}, {"2", "3"}};
  vector<pair<string, string>> expectedFollowsStarPairs = {
      {"1", "2"}, {"1", "3"}, {"2", "3"}};
  vector<pair<string, string>> expectedParentChildPairs = {{"3", "4"},
                                                           {"3", "5"}};
  vector<pair<string, string>> expectedParentChildStarPairs = {{"3", "4"},
                                                               {"3", "5"}};
  vector<pair<string, string>> expectedModifiesPairs = {
      {"1", "p"}, {"2", "q"}, {"4", "r"}, {"3", "r"}};
  vector<pair<string, string>> expectedUsesPairs = {
      {"3", "p"}, {"3", "q"}, {"3", "x"}, {"3", "y"}, {"5", "p"}};
  validateEntities(reader, expectedVars, expectedConstants, expectedProcedures,
                   expectedReadStmts, expectedPrintStmts, expectedAssignStmts,
                   expectedCallStmts, expectedWhileStmts, expectedIfStmts);
  validateFollows(reader, expectedFollowsPairs, expectedFollowsStarPairs);
  validateParents(reader, expectedParentChildPairs,
                  expectedParentChildStarPairs);
  validateModifies(reader, expectedModifiesPairs);
  validateUses(reader, expectedUsesPairs);
  REQUIRE(reader.getExactAssignPattern("_", "_", false).empty());
  REQUIRE(reader.getPartialAssignPattern("_", "_", false).empty());
}

TEST_CASE("SP-PKB integration - assign pattern with all operators") {
  string input =
      "procedure simple {"
      "read a; read b; read c; read d; read e; read f;"  // 1-6
      "x = a + b * c - d / e % f;"                       // 7
      "y = (a + b) * (c - d) / (e % f);"                 // 8
      "z = a * (b + c * d - e / f) % g;"                 // 9
      "a = a - b / c * d + e % f * g;"                   // 10
      "b = (a * b - c) % (d + e / f);"                   // 11
      "c = a / (b + c) * d - e % f + g;"                 // 12
      "d = a + b * (c % d - e) / f;"                     // 13
      "e = (a % b) * c - d / (e + f);"                   // 14
      "f = a / b * (c + d) % e - f;"                     // 15
      "g = (a + b % c) * (d - e / f);"                   // 16
      "x = a - b * c;"                                   // 17
      "x = a - b * c;"                                   // 18
      "x = a * b + c;"                                   // 19
      "x = a / b - c * d;"                               // 20
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader &reader = pkb.getReader();
  set<string> expectedVars = {"a", "b", "c", "d", "e", "f", "g", "x", "y", "z"};
  set<string> expectedConstants = {};
  set<string> expectedProcedures = {"simple"};
  set<string> expectedReadStmts = {"1", "2", "3", "4", "5", "6"};
  set<string> expectedPrintStmts = {};
  set<string> expectedAssignStmts = {"7",  "8",  "9",  "10", "11", "12", "13",
                                     "14", "15", "16", "17", "18", "19", "20"};
  set<string> expectedCallStmts = {};
  set<string> expectedWhileStmts = {};
  set<string> expectedIfStmts = {};
  vector<pair<string, string>> expectedFollowsPairs = {
      {"1", "2"},   {"2", "3"},   {"3", "4"},   {"4", "5"},   {"5", "6"},
      {"6", "7"},   {"7", "8"},   {"8", "9"},   {"9", "10"},  {"10", "11"},
      {"11", "12"}, {"12", "13"}, {"13", "14"}, {"14", "15"}, {"15", "16"},
      {"16", "17"}, {"17", "18"}, {"18", "19"}, {"19", "20"}};
  vector<pair<string, string>> expectedFollowsStarPairs = {
      {"1", "2"},   {"1", "3"},   {"1", "4"},   {"1", "5"},   {"1", "6"},
      {"1", "7"},   {"1", "8"},   {"1", "9"},   {"1", "10"},  {"1", "11"},
      {"1", "12"},  {"1", "13"},  {"1", "14"},  {"1", "15"},  {"1", "16"},
      {"1", "17"},  {"1", "18"},  {"1", "19"},  {"1", "20"},  {"2", "3"},
      {"2", "4"},   {"2", "5"},   {"2", "6"},   {"2", "7"},   {"2", "8"},
      {"2", "9"},   {"2", "10"},  {"2", "11"},  {"2", "12"},  {"2", "13"},
      {"2", "14"},  {"2", "15"},  {"2", "16"},  {"2", "17"},  {"2", "18"},
      {"2", "19"},  {"2", "20"},  {"3", "4"},   {"3", "5"},   {"3", "6"},
      {"3", "7"},   {"3", "8"},   {"3", "9"},   {"3", "10"},  {"3", "11"},
      {"3", "12"},  {"3", "13"},  {"3", "14"},  {"3", "15"},  {"3", "16"},
      {"3", "17"},  {"3", "18"},  {"3", "19"},  {"3", "20"},  {"4", "5"},
      {"4", "6"},   {"4", "7"},   {"4", "8"},   {"4", "9"},   {"4", "10"},
      {"4", "11"},  {"4", "12"},  {"4", "13"},  {"4", "14"},  {"4", "15"},
      {"4", "16"},  {"4", "17"},  {"4", "18"},  {"4", "19"},  {"4", "20"},
      {"5", "6"},   {"5", "7"},   {"5", "8"},   {"5", "9"},   {"5", "10"},
      {"5", "11"},  {"5", "12"},  {"5", "13"},  {"5", "14"},  {"5", "15"},
      {"5", "16"},  {"5", "17"},  {"5", "18"},  {"5", "19"},  {"5", "20"},
      {"6", "7"},   {"6", "8"},   {"6", "9"},   {"6", "10"},  {"6", "11"},
      {"6", "12"},  {"6", "13"},  {"6", "14"},  {"6", "15"},  {"6", "16"},
      {"6", "17"},  {"6", "18"},  {"6", "19"},  {"6", "20"},  {"7", "8"},
      {"7", "9"},   {"7", "10"},  {"7", "11"},  {"7", "12"},  {"7", "13"},
      {"7", "14"},  {"7", "15"},  {"7", "16"},  {"7", "17"},  {"7", "18"},
      {"7", "19"},  {"7", "20"},  {"8", "9"},   {"8", "10"},  {"8", "11"},
      {"8", "12"},  {"8", "13"},  {"8", "14"},  {"8", "15"},  {"8", "16"},
      {"8", "17"},  {"8", "18"},  {"8", "19"},  {"8", "20"},  {"9", "10"},
      {"9", "11"},  {"9", "12"},  {"9", "13"},  {"9", "14"},  {"9", "15"},
      {"9", "16"},  {"9", "17"},  {"9", "18"},  {"9", "19"},  {"9", "20"},
      {"10", "11"}, {"10", "12"}, {"10", "13"}, {"10", "14"}, {"10", "15"},
      {"10", "16"}, {"10", "17"}, {"10", "18"}, {"10", "19"}, {"10", "20"},
      {"11", "12"}, {"11", "13"}, {"11", "14"}, {"11", "15"}, {"11", "16"},
      {"11", "17"}, {"11", "18"}, {"11", "19"}, {"11", "20"}, {"12", "13"},
      {"12", "14"}, {"12", "15"}, {"12", "16"}, {"12", "17"}, {"12", "18"},
      {"12", "19"}, {"12", "20"}, {"13", "14"}, {"13", "15"}, {"13", "16"},
      {"13", "17"}, {"13", "18"}, {"13", "19"}, {"13", "20"}, {"14", "15"},
      {"14", "16"}, {"14", "17"}, {"14", "18"}, {"14", "19"}, {"14", "20"},
      {"15", "16"}, {"15", "17"}, {"15", "18"}, {"15", "19"}, {"15", "20"},
      {"16", "17"}, {"16", "18"}, {"16", "19"}, {"16", "20"}, {"17", "18"},
      {"17", "19"}, {"17", "20"}, {"18", "19"}, {"18", "20"}, {"19", "20"}};
  vector<pair<string, string>> expectedParentChildPairs = {};
  vector<pair<string, string>> expectedParentChildStarPairs = {};
  vector<pair<string, string>> expectedModifiesPairs = {
      {"1", "a"},  {"2", "b"},  {"3", "c"},  {"4", "d"},  {"5", "e"},
      {"6", "f"},  {"7", "x"},  {"8", "y"},  {"9", "z"},  {"10", "a"},
      {"11", "b"}, {"12", "c"}, {"13", "d"}, {"14", "e"}, {"15", "f"},
      {"16", "g"}, {"17", "x"}, {"18", "x"}, {"19", "x"}, {"20", "x"}};
  vector<pair<string, string>> expectedUsesPairs = {
      {"7", "a"},  {"8", "a"},  {"9", "a"},  {"10", "a"}, {"11", "a"},
      {"12", "a"}, {"13", "a"}, {"14", "a"}, {"15", "a"}, {"16", "a"},
      {"17", "a"}, {"18", "a"}, {"19", "a"}, {"20", "a"}, {"7", "b"},
      {"8", "b"},  {"9", "b"},  {"10", "b"}, {"11", "b"}, {"12", "b"},
      {"13", "b"}, {"14", "b"}, {"15", "b"}, {"16", "b"}, {"17", "b"},
      {"18", "b"}, {"19", "b"}, {"20", "b"}, {"7", "c"},  {"8", "c"},
      {"9", "c"},  {"10", "c"}, {"11", "c"}, {"12", "c"}, {"13", "c"},
      {"14", "c"}, {"15", "c"}, {"16", "c"}, {"17", "c"}, {"18", "c"},
      {"19", "c"}, {"20", "c"}, {"7", "d"},  {"8", "d"},  {"9", "d"},
      {"10", "d"}, {"11", "d"}, {"12", "d"}, {"13", "d"}, {"14", "d"},
      {"15", "d"}, {"16", "d"}, {"20", "d"}, {"7", "e"},  {"8", "e"},
      {"9", "e"},  {"10", "e"}, {"11", "e"}, {"12", "e"}, {"13", "e"},
      {"14", "e"}, {"15", "e"}, {"16", "e"}, {"7", "f"},  {"8", "f"},
      {"9", "f"},  {"10", "f"}, {"11", "f"}, {"12", "f"}, {"13", "f"},
      {"14", "f"}, {"15", "f"}, {"16", "f"}, {"9", "g"},  {"10", "g"},
      {"12", "g"},
  };
  validateEntities(reader, expectedVars, expectedConstants, expectedProcedures,
                   expectedReadStmts, expectedPrintStmts, expectedAssignStmts,
                   expectedCallStmts, expectedWhileStmts, expectedIfStmts);
  validateFollows(reader, expectedFollowsPairs, expectedFollowsStarPairs);
  validateParents(reader, expectedParentChildPairs,
                  expectedParentChildStarPairs);
  validateModifies(reader, expectedModifiesPairs);
  validateUses(reader, expectedUsesPairs);
  REQUIRE(reader.getExactAssignPattern("x", " a b c * + d e / f % - ", false) ==
          vector<string>{"7"});
  REQUIRE(reader.getExactAssignPattern("y", " a b + c d - * e f % / ", false) ==
          vector<string>{"8"});
  REQUIRE(reader.getExactAssignPattern("z", " a b c d * + e f / - * g % ",
                                       false) == vector<string>{"9"});
  REQUIRE(reader.getExactAssignPattern("a", " a b c / d * - e f % g * + ",
                                       false) == vector<string>{"10"});
  REQUIRE(reader.getExactAssignPattern("b", " a b * c - d e f / + % ", false) ==
          vector<string>{"11"});
  REQUIRE(reader.getExactAssignPattern("c", " a b c + / d * e f % - g + ",
                                       false) == vector<string>{"12"});
  REQUIRE(reader.getExactAssignPattern("d", " a b c d % e - * f / + ", false) ==
          vector<string>{"13"});
  REQUIRE(reader.getExactAssignPattern("e", " a b % c * d e f + / - ", false) ==
          vector<string>{"14"});
  REQUIRE(reader.getExactAssignPattern("f", " a b / c d + * e % f - ", false) ==
          vector<string>{"15"});
  REQUIRE(reader.getExactAssignPattern("g", " a b c % + d e f / - * ", false) ==
          vector<string>{"16"});
  REQUIRE(reader.getExactAssignPattern("x", " a b c * - ", false) ==
          vector<string>{"18", "17"});
  REQUIRE(reader.getExactAssignPattern("x", " a b * c + ", false) ==
          vector<string>{"19"});
  REQUIRE(reader.getExactAssignPattern("x", " a b / c d * - ", false) ==
          vector<string>{"20"});
  REQUIRE(reader.getExactAssignPattern("_", "_", false) ==
          vector<string>{"20", "19", "18", "17", "16", "15", "14", "13", "12",
                         "11", "10", "9", "8", "7"});

  REQUIRE(reader.getPartialAssignPattern("x", " a b c * + ", false) ==
          vector<string>{"7"});
  REQUIRE(reader.getPartialAssignPattern("y", " a b + c d - * ", false) ==
          vector<string>{"8"});
  REQUIRE(reader.getPartialAssignPattern("_", " e f / ", false) ==
          vector<string>{"16", "11", "9"});
  REQUIRE(reader.getPartialAssignPattern("_", " a b c / d * - e f % g * + ",
                                         false) == vector<string>{"10"});
  REQUIRE(reader.getPartialAssignPattern("_", " e f % ", false) ==
          vector<string>{"12", "10", "8"});
  REQUIRE(reader.getPartialAssignPattern("_", " c d % ", false) ==
          vector<string>{"13"});
  REQUIRE(reader.getPartialAssignPattern("e", " d e f + / ", false) ==
          vector<string>{"14"});
  REQUIRE(reader.getPartialAssignPattern("f", " a b / c d + * ", false) ==
          vector<string>{"15"});
  REQUIRE(reader.getPartialAssignPattern("g", " a b c % + d e f / - * ",
                                         false) == vector<string>{"16"});
  REQUIRE(reader.getPartialAssignPattern("x", "_", false) ==
          vector<string>{"7", "17", "18", "19", "20"});
}

TEST_CASE(
    "SP-PKB integration - nested if-while, while-if and multiple "
    "assign/control variables") {
  string input =
      "procedure nestedWhile {"
      "    read a; read b; read c; read d; read e; read f;"  // 1-6
      "    x = a + b * c - d / e % f;"                       // 7
      "    while (a == b) {"                                 // 8
      "        y = (a + b) * (c - d) / (e % f);"             // 9
      "        if (c != a) then {"                           // 10
      "            z = a * (b + c * d - e / f) % g;"         // 11
      "        } else {"
      "            a = a - b / c * d + e % f * g;"  // 12
      "        }"
      "        while ((a + b * 2) == (x - y % 3)) {"  // 13
      "            b = (a * b - c) % (d + e / f);"    // 14
      "            c = a / (b + c) * d - e % f + g;"  // 15
      "        }"
      "    }"
      "    if ((c + d) > (e - f)) then {"         // 16
      "        while (a < b) {"                   // 17
      "            d = a + b * (c % d - e) / f;"  // 18
      "        }"
      "        e = (a % b) * c - d / (e + f);"  // 19
      "    } else {"
      "        f = a / b * (c + d) % e - f;"  // 20
      "    }"
      "    g = (a + b % c) * (d - e / f);"       // 21
      "    print a; print b; print c; print d;"  // 22-25
      "    print e; print f; print g;"           // 26-28
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader &reader = pkb.getReader();
  set<string> expectedVars = {"a", "b", "c", "d", "e", "f", "g", "x", "y", "z"};
  set<string> expectedConstants = {"2", "3"};
  set<string> expectedProcedures = {"nestedWhile"};
  set<string> expectedReadStmts = {"1", "2", "3", "4", "5", "6"};
  set<string> expectedPrintStmts = {"22", "23", "24", "25", "26", "27", "28"};
  set<string> expectedAssignStmts = {"7",  "9",  "11", "12", "14",
                                     "15", "18", "19", "20", "21"};
  set<string> expectedCallStmts = {};
  set<string> expectedWhileStmts = {"8", "13", "17"};
  set<string> expectedIfStmts = {"10", "16"};
  vector<pair<string, string>> expectedFollowsPairs = {
      {"1", "2"},   {"2", "3"},   {"3", "4"},   {"4", "5"},   {"5", "6"},
      {"6", "7"},   {"7", "8"},   {"8", "16"},  {"16", "21"}, {"9", "10"},
      {"10", "13"}, {"14", "15"}, {"17", "19"}, {"21", "22"}, {"22", "23"},
      {"23", "24"}, {"24", "25"}, {"25", "26"}, {"26", "27"}, {"27", "28"}};
  vector<pair<string, string>> expectedFollowsStarPairs = {
      {"1", "2"},   {"1", "3"},   {"1", "4"},   {"1", "5"},   {"1", "6"},
      {"1", "7"},   {"1", "8"},   {"1", "16"},  {"1", "21"},  {"1", "22"},
      {"1", "23"},  {"1", "24"},  {"1", "25"},  {"1", "26"},  {"1", "27"},
      {"1", "28"},  {"2", "3"},   {"2", "4"},   {"2", "5"},   {"2", "6"},
      {"2", "7"},   {"2", "8"},   {"2", "16"},  {"2", "21"},  {"2", "22"},
      {"2", "23"},  {"2", "24"},  {"2", "25"},  {"2", "26"},  {"2", "27"},
      {"2", "28"},  {"3", "4"},   {"3", "5"},   {"3", "6"},   {"3", "7"},
      {"3", "8"},   {"3", "16"},  {"3", "21"},  {"3", "22"},  {"3", "23"},
      {"3", "24"},  {"3", "25"},  {"3", "26"},  {"3", "27"},  {"3", "28"},
      {"4", "5"},   {"4", "6"},   {"4", "7"},   {"4", "8"},   {"4", "16"},
      {"4", "21"},  {"4", "22"},  {"4", "23"},  {"4", "24"},  {"4", "25"},
      {"4", "26"},  {"4", "27"},  {"4", "28"},  {"5", "6"},   {"5", "7"},
      {"5", "8"},   {"5", "16"},  {"5", "21"},  {"5", "22"},  {"5", "23"},
      {"5", "24"},  {"5", "25"},  {"5", "26"},  {"5", "27"},  {"5", "28"},
      {"6", "7"},   {"6", "8"},   {"6", "16"},  {"6", "21"},  {"6", "22"},
      {"6", "23"},  {"6", "24"},  {"6", "25"},  {"6", "26"},  {"6", "27"},
      {"6", "28"},  {"7", "8"},   {"7", "16"},  {"7", "21"},  {"7", "22"},
      {"7", "23"},  {"7", "24"},  {"7", "25"},  {"7", "26"},  {"7", "27"},
      {"7", "28"},  {"8", "16"},  {"8", "21"},  {"8", "22"},  {"8", "23"},
      {"8", "24"},  {"8", "25"},  {"8", "26"},  {"8", "27"},  {"8", "28"},
      {"9", "10"},  {"9", "13"},  {"10", "13"}, {"14", "15"}, {"16", "21"},
      {"16", "22"}, {"16", "23"}, {"16", "24"}, {"16", "25"}, {"16", "26"},
      {"16", "27"}, {"16", "28"}, {"17", "19"}, {"21", "22"}, {"21", "23"},
      {"21", "24"}, {"21", "25"}, {"21", "26"}, {"21", "27"}, {"21", "28"},
      {"22", "23"}, {"22", "24"}, {"22", "25"}, {"22", "26"}, {"22", "27"},
      {"22", "28"}, {"23", "24"}, {"23", "25"}, {"23", "26"}, {"23", "27"},
      {"23", "28"}, {"24", "25"}, {"24", "26"}, {"24", "27"}, {"24", "28"},
      {"25", "26"}, {"25", "27"}, {"25", "28"}, {"26", "27"}, {"26", "28"},
      {"27", "28"}};
  vector<pair<string, string>> expectedParentChildPairs = {
      {"8", "9"},   {"8", "10"},  {"8", "13"},  {"10", "11"},
      {"10", "12"}, {"13", "14"}, {"13", "15"}, {"16", "17"},
      {"16", "19"}, {"16", "20"}, {"17", "18"},
  };
  vector<pair<string, string>> expectedParentChildStarPairs = {
      {"8", "9"},   {"8", "10"},  {"8", "11"},  {"8", "12"},
      {"8", "13"},  {"8", "14"},  {"8", "15"},  {"10", "11"},
      {"10", "12"}, {"13", "14"}, {"13", "15"}, {"16", "17"},
      {"16", "18"}, {"16", "19"}, {"16", "20"}, {"17", "18"}};
  vector<pair<string, string>> expectedModifiesPairs = {
      {"1", "a"},  {"12", "a"}, {"10", "a"}, {"8", "a"},  {"2", "b"},
      {"14", "b"}, {"13", "b"}, {"8", "b"},  {"3", "c"},  {"15", "c"},
      {"13", "c"}, {"8", "c"},  {"4", "d"},  {"18", "d"}, {"17", "d"},
      {"16", "d"}, {"5", "e"},  {"19", "e"}, {"16", "e"}, {"6", "f"},
      {"20", "f"}, {"16", "f"}, {"7", "x"},  {"9", "y"},  {"8", "y"},
      {"11", "z"}, {"10", "z"}, {"8", "z"},  {"21", "g"}};
  vector<pair<string, string>> expectedUsesPairs = {
      {"7", "a"},  {"8", "a"},  {"9", "a"},  {"10", "a"}, {"11", "a"},
      {"12", "a"}, {"13", "a"}, {"14", "a"}, {"15", "a"}, {"16", "a"},
      {"17", "a"}, {"18", "a"}, {"19", "a"}, {"20", "a"}, {"21", "a"},
      {"22", "a"}, {"7", "b"},  {"8", "b"},  {"9", "b"},  {"10", "b"},
      {"11", "b"}, {"12", "b"}, {"13", "b"}, {"14", "b"}, {"15", "b"},
      {"16", "b"}, {"17", "b"}, {"18", "b"}, {"19", "b"}, {"20", "b"},
      {"21", "b"}, {"23", "b"}, {"7", "c"},  {"8", "c"},  {"9", "c"},
      {"10", "c"}, {"11", "c"}, {"12", "c"}, {"13", "c"}, {"14", "c"},
      {"15", "c"}, {"16", "c"}, {"17", "c"}, {"18", "c"}, {"19", "c"},
      {"20", "c"}, {"21", "c"}, {"24", "c"}, {"7", "d"},  {"8", "d"},
      {"9", "d"},  {"10", "d"}, {"11", "d"}, {"12", "d"}, {"13", "d"},
      {"14", "d"}, {"15", "d"}, {"16", "d"}, {"17", "d"}, {"18", "d"},
      {"19", "d"}, {"20", "d"}, {"21", "d"}, {"25", "d"}, {"7", "e"},
      {"8", "e"},  {"9", "e"},  {"10", "e"}, {"11", "e"}, {"12", "e"},
      {"13", "e"}, {"14", "e"}, {"15", "e"}, {"16", "e"}, {"17", "e"},
      {"18", "e"}, {"19", "e"}, {"20", "e"}, {"21", "e"}, {"26", "e"},
      {"7", "f"},  {"8", "f"},  {"9", "f"},  {"10", "f"}, {"11", "f"},
      {"12", "f"}, {"13", "f"}, {"14", "f"}, {"15", "f"}, {"16", "f"},
      {"17", "f"}, {"18", "f"}, {"19", "f"}, {"20", "f"}, {"21", "f"},
      {"27", "f"}, {"8", "g"},  {"10", "g"}, {"11", "g"}, {"12", "g"},
      {"13", "g"}, {"15", "g"}, {"28", "g"}, {"13", "x"}, {"8", "x"},
      {"8", "y"},  {"13", "y"},
  };
  validateEntities(reader, expectedVars, expectedConstants, expectedProcedures,
                   expectedReadStmts, expectedPrintStmts, expectedAssignStmts,
                   expectedCallStmts, expectedWhileStmts, expectedIfStmts);
  validateFollows(reader, expectedFollowsPairs, expectedFollowsStarPairs);
  validateParents(reader, expectedParentChildPairs,
                  expectedParentChildStarPairs);
  validateModifies(reader, expectedModifiesPairs);
  validateUses(reader, expectedUsesPairs);
  REQUIRE(reader.getExactAssignPattern("x", " a b c * + d e / f % - ", false) ==
          vector<string>{"7"});
  REQUIRE(reader.getExactAssignPattern("y", " a b + c d - * e f % / ", false) ==
          vector<string>{"9"});
  REQUIRE(reader.getExactAssignPattern("z", " a b c d * + e f / - * g % ",
                                       false) == vector<string>{"11"});
  REQUIRE(reader.getExactAssignPattern("a", " a b c / d * - e f % g * + ",
                                       false) == vector<string>{"12"});
  REQUIRE(reader.getExactAssignPattern("b", " a b * c - d e f / + % ", false) ==
          vector<string>{"14"});
  REQUIRE(reader.getExactAssignPattern("c", " a b c + / d * e f % - g + ",
                                       false) == vector<string>{"15"});
  REQUIRE(reader.getExactAssignPattern("d", " a b c d % e - * f / + ", false) ==
          vector<string>{"18"});
  REQUIRE(reader.getExactAssignPattern("e", " a b % c * d e f + / - ", false) ==
          vector<string>{"19"});
  REQUIRE(reader.getExactAssignPattern("f", " a b / c d + * e % f - ", false) ==
          vector<string>{"20"});
  REQUIRE(reader.getExactAssignPattern("g", " a b c % + d e f / - * ", false) ==
          vector<string>{"21"});
  REQUIRE(
      reader.getExactAssignPattern("_", "_", false) ==
      vector<string>{"21", "19", "15", "11", "14", "20", "9", "12", "18", "7"});

  REQUIRE(reader.getPartialAssignPattern("x", " a b c * - ", false) ==
          vector<string>{});
  REQUIRE(reader.getPartialAssignPattern("x", " a b c * + ", false) ==
          vector<string>{"7"});
  REQUIRE(reader.getPartialAssignPattern("_", " e f % ", false) ==
          vector<string>{"15", "9", "12"});
  REQUIRE(reader.getPartialAssignPattern("_", " e f / ", false) ==
          vector<string>{"21", "11", "14"});
  REQUIRE(reader.getPartialAssignPattern("_", " d e f + / ", false) ==
          vector<string>{"19"});
  REQUIRE(reader.getPartialAssignPattern("g", " a b c % + ", false) ==
          vector<string>{"21"});
}

TEST_CASE("SP-PKB integration - duplicate proc names throw exception") {
  string input =
      "procedure First {"
      "    read x;"
      "    read z;"
      "}"
      "procedure First {"
      "    print z;"
      "    read x;"
      "}";

  SourceProcessor sp;
  PKB pkb;
  REQUIRE_THROWS_MATCHES(sp.processContent(input, pkb.getWriter()),
                         DuplicateProcNameException,
                         Catch::Message("Duplicate procedure name 'First', "
                                        "this name has already been used!"));
}

TEST_CASE("SP-PKB integration - undefined proc calls throw exception") {
  string input =
      "procedure First {"
      "    call Second;"
      "    read z;"
      "}"
      "procedure Second {"
      "    call Third;"
      "    read x;"
      "}"
      "procedure Third {"
      "    call Fourth;"
      "}";

  SourceProcessor sp;
  PKB pkb;
  REQUIRE_THROWS_MATCHES(sp.processContent(input, pkb.getWriter()),
                         UndefinedProcCallException,
                         Catch::Message("Procedure name 'Fourth' called has "
                                        "not been defined in the program!"));
}

TEST_CASE("SP-PKB integration - cyclic calls throw exception") {
  string input =
      "procedure First {"
      "    read x;"
      "    call First;"
      "}";

  SourceProcessor sp;
  PKB pkb;
  REQUIRE_THROWS_MATCHES(sp.processContent(input, pkb.getWriter()),
                         CyclicProcCallException,
                         Catch::Message("Cyclic procedure calls detected!"));
}
