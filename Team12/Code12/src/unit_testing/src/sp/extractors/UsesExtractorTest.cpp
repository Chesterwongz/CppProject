#include <map>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "../ast/TNodeUtils.h"
#include "../mocks/MockData.h"
#include "../mocks/MockPKBWriter.h"
#include "AbstractionTypes.h"
#include "ExtractorUtils.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/StmtListNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::map,
    std::set, std::unordered_map, std::unordered_set;

TEST_CASE("UsesExtractor - no uses") {
  //    string input =
  //        "procedure simple {"
  //        "read y;"
  //        "read y;"
  //        "}";
  unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
  unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
  unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
  stmtListNode->addChild(makeReadNode(1, "y"));
  stmtListNode->addChild(makeReadNode(2, "y"));
  procNode->addChild(std::move(stmtListNode));
  programNode->addChild(std::move(procNode));

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(*programNode, mockPKB, AbstractionType::USES);
  unordered_map<string, unordered_set<int>> expected = {};
  REQUIRE(mockPKB.isUsesEqual(expected));

  unordered_map<string, unordered_set<string>> expectedVarToProcName =
      unordered_map<string, unordered_set<string>>();
  REQUIRE(mockPKB.isUsesEqual(expectedVarToProcName));
}

TEST_CASE("UsesExtractor with parser - no uses") {
  string input =
      "procedure simple {"
      "read y;"
      "read y;"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::USES);
  unordered_map<string, unordered_set<int>> expected = {};
  REQUIRE(mockPKB.isUsesEqual(expected));

  unordered_map<string, unordered_set<string>> expectedVarToProcName =
      unordered_map<string, unordered_set<string>>();
  REQUIRE(mockPKB.isUsesEqual(expectedVarToProcName));
}

TEST_CASE("UsesExtractor - non-nesting, 1 uses") {
  //    string input =
  //        "procedure simple {"
  //        "read y;"
  //        "print x;"
  //        "x = y + 1;"
  //        "}";
  unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
  unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
  unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
  stmtListNode->addChild(makeReadNode(1, "y"));
  stmtListNode->addChild(makePrintNode(2, "x"));
  stmtListNode->addChild(makeAssignWithPlusNode(3, "x", "y", "1"));
  procNode->addChild(std::move(stmtListNode));
  programNode->addChild(std::move(procNode));

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(*programNode, mockPKB, AbstractionType::USES);
  unordered_map<string, unordered_set<int>> expected = {};
  expected["x"] = {2};
  expected["y"] = {3};
  REQUIRE(mockPKB.isUsesEqual(expected));

  unordered_map<string, unordered_set<string>> expectedVarToProcName =
      unordered_map<string, unordered_set<string>>();
  expectedVarToProcName["x"] = {"simple"};
  expectedVarToProcName["y"] = {"simple"};
  REQUIRE(mockPKB.isUsesEqual(expectedVarToProcName));
}

TEST_CASE("UsesExtractor with parser - non-nesting, 1 uses") {
  string input =
      "procedure simple {"
      "read y;"
      "print x;"
      "x = y + 1;"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::USES);
  unordered_map<string, unordered_set<int>> expected = {};
  expected["x"] = {2};
  expected["y"] = {3};
  REQUIRE(mockPKB.isUsesEqual(expected));
}

TEST_CASE("UsesExtractor - if node") {
  //    string input =
  //        "procedure simple {"
  // 1       "read y;"
  // 2       "print x;"
  // 3       "if (num1 < num2) then {"
  // 4       "print z;"
  //        "} else {"
  // 5       "x = y + 1;"
  //        "}"
  //        "}";
  unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
  unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
  unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
  stmtListNode->addChild(makeReadNode(1, "y"));
  stmtListNode->addChild(makePrintNode(2, "x"));
  // make if node
  unique_ptr<IfNode> ifNode = make_unique<IfNode>(3);
  ifNode->addChild(makeLtNode("num1", "num2"));
  unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
  thenStmtListNode->addChild(makePrintNode(4, "z"));
  ifNode->addChild(std::move(thenStmtListNode));
  unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
  elseStmtListNode->addChild(makeAssignWithPlusNode(5, "x", "y", "1"));
  ifNode->addChild(std::move(elseStmtListNode));
  // add if to proc
  stmtListNode->addChild(std::move(ifNode));
  procNode->addChild(std::move(stmtListNode));
  programNode->addChild(std::move(procNode));

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(*programNode, mockPKB, AbstractionType::USES);
  unordered_map<string, unordered_set<int>> expected = {};
  expected["x"] = {2};
  expected["y"] = {3, 5};
  expected["z"] = {3, 4};
  expected["num1"] = {3};
  expected["num2"] = {3};
  REQUIRE(mockPKB.isUsesEqual(expected));

  unordered_map<string, unordered_set<string>> expectedVarToProcName =
      unordered_map<string, unordered_set<string>>();
  expectedVarToProcName["x"] = {"simple"};
  expectedVarToProcName["y"] = {"simple"};
  expectedVarToProcName["z"] = {"simple"};
  expectedVarToProcName["num1"] = {"simple"};
  expectedVarToProcName["num2"] = {"simple"};
  REQUIRE(mockPKB.isUsesEqual(expectedVarToProcName));
}

TEST_CASE("UsesExtractor with parser - if node") {
  string input =
      "procedure simple {"
      "read y;"
      "print x;"
      "if (num1 < num2) then {"
      "print z;"
      "} else {"
      "x = y + 1;"
      "}"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::USES);
  unordered_map<string, unordered_set<int>> expected = {};
  expected["x"] = {2};
  expected["y"] = {3, 5};
  expected["z"] = {3, 4};
  expected["num1"] = {3};
  expected["num2"] = {3};
  REQUIRE(mockPKB.isUsesEqual(expected));

  unordered_map<string, unordered_set<string>> expectedVarToProcName =
      unordered_map<string, unordered_set<string>>();
  expectedVarToProcName["x"] = {"simple"};
  expectedVarToProcName["y"] = {"simple"};
  expectedVarToProcName["z"] = {"simple"};
  expectedVarToProcName["num1"] = {"simple"};
  expectedVarToProcName["num2"] = {"simple"};
  REQUIRE(mockPKB.isUsesEqual(expectedVarToProcName));
}

TEST_CASE("UsesExtractor - if in while node") {
  //    string input =
  //        "procedure simple {"
  // 1       "read x"
  // 2       "read y"
  // 3       "while (x < y) {"
  // 4       "if (x == y) then {"
  // 5       "x = y + 1;"
  // 6       "} else { print w; }"
  // 7       "print z;"
  //        "}"
  // 8       "read num1;"
  //        "}";
  unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
  unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
  unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
  stmtListNode->addChild(makeReadNode(1, "x"));
  stmtListNode->addChild(makeReadNode(2, "y"));
  // make while node
  unique_ptr<WhileNode> whileNode = make_unique<WhileNode>(3);
  whileNode->addChild(makeLtNode("x", "y"));
  unique_ptr<StmtListNode> whileStmtListNode = make_unique<StmtListNode>();
  // make if node
  unique_ptr<IfNode> ifNode = make_unique<IfNode>(4);
  ifNode->addChild(makeEqNode("x", "y"));
  unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
  thenStmtListNode->addChild(makeAssignWithPlusNode(5, "x", "y", "1"));
  ifNode->addChild(std::move(thenStmtListNode));
  unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
  elseStmtListNode->addChild(makePrintNode(6, "w"));
  ifNode->addChild(std::move(elseStmtListNode));
  // add if to while
  whileStmtListNode->addChild(std::move(ifNode));
  whileStmtListNode->addChild(makePrintNode(7, "z"));
  // add while to proc
  whileNode->addChild(std::move(whileStmtListNode));
  stmtListNode->addChild(std::move(whileNode));
  stmtListNode->addChild(makeReadNode(8, "num1"));
  procNode->addChild(std::move(stmtListNode));
  programNode->addChild(std::move(procNode));

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(*programNode, mockPKB, AbstractionType::USES);
  unordered_map<string, unordered_set<int>> expected = {};
  expected["x"] = {3, 4};
  expected["y"] = {3, 4, 5};
  expected["w"] = {3, 4, 6};
  expected["z"] = {3, 7};
  REQUIRE(mockPKB.isUsesEqual(expected));

  unordered_map<string, unordered_set<string>> expectedVarToProcName =
      unordered_map<string, unordered_set<string>>();
  expectedVarToProcName["x"] = {"simple"};
  expectedVarToProcName["y"] = {"simple"};
  expectedVarToProcName["w"] = {"simple"};
  expectedVarToProcName["z"] = {"simple"};
  REQUIRE(mockPKB.isUsesEqual(expectedVarToProcName));
}

TEST_CASE("UsesExtractor with parser - if in while node") {
  string input =
      "procedure simple {"
      "read x;"
      "read y;"
      "while (x < y) {"
      "if (x == y) then {"
      "x = y + 1;"
      "} else { print w; }"
      "print z;"
      "}"
      "read num1;"
      "}";
  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::USES);
  unordered_map<string, unordered_set<int>> expected = {};
  expected["x"] = {3, 4};
  expected["y"] = {3, 4, 5};
  expected["w"] = {3, 4, 6};
  expected["z"] = {3, 7};
  REQUIRE(mockPKB.isUsesEqual(expected));

  unordered_map<string, unordered_set<string>> expectedVarToProcName =
      unordered_map<string, unordered_set<string>>();
  expectedVarToProcName["x"] = {"simple"};
  expectedVarToProcName["y"] = {"simple"};
  expectedVarToProcName["z"] = {"simple"};
  expectedVarToProcName["w"] = {"simple"};
  REQUIRE(mockPKB.isUsesEqual(expectedVarToProcName));
}

TEST_CASE("UsesExtractor with parser - no proc call") {
  string input =
      "procedure simple {"
      "print x;"
      "print y;"
      "}"
      "procedure simple2 {"
      "print x;"
      "}"
      "procedure simple3 {"
      "x = y + 1;"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::USES);
  unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
  expectedVarToStmtNum["x"] = {1, 3};
  expectedVarToStmtNum["y"] = {2, 4};
  REQUIRE(mockPKB.isUsesEqual(expectedVarToStmtNum));

  unordered_map<string, unordered_set<string>> expectedVarToProcName =
      unordered_map<string, unordered_set<string>>();
  expectedVarToProcName["x"] = {"simple", "simple2"};
  expectedVarToProcName["y"] = {"simple", "simple3"};
  REQUIRE(mockPKB.isUsesEqual(expectedVarToProcName));
}

TEST_CASE("UsesExtractor with parser - 3 nested if statements") {
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::USES);
  unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
  expectedVarToStmtNum["v"] = {3, 5, 11};
  expectedVarToStmtNum["w"] = {3, 5};
  expectedVarToStmtNum["x"] = {3, 5, 7, 9};
  expectedVarToStmtNum["y"] = {3, 5, 7};
  expectedVarToStmtNum["z"] = {3, 5, 10};
  REQUIRE(mockPKB.isUsesEqual(expectedVarToStmtNum));

  unordered_map<string, unordered_set<string>> expectedVarToProcName =
      unordered_map<string, unordered_set<string>>();
  expectedVarToProcName["v"] = {"multipleIf"};
  expectedVarToProcName["w"] = {"multipleIf"};
  expectedVarToProcName["x"] = {"multipleIf"};
  expectedVarToProcName["y"] = {"multipleIf"};
  expectedVarToProcName["z"] = {"multipleIf"};
  REQUIRE(mockPKB.isUsesEqual(expectedVarToProcName));
}
