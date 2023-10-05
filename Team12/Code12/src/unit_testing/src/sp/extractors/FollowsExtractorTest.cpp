#include <memory>
#include <set>
#include <unordered_map>
#include <vector>
#include <catch.hpp>

#include "../ast/TNodeUtils.h"
#include "ExtractorUtils.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/StmtListNode.h"

using std::unique_ptr, std::make_unique, std::vector, std::string,
    std::unordered_map, std::set;

TEST_CASE("FollowsExtractor Simple Statement list") {
  //    string input =
  //        "procedure simple {"
  //        "read num1;"
  //        "read num2;"
  //        "read num3;"
  //        "}";
  unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
  unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
  unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
  stmtListNode->addChild(makeReadNode(1, "num1"));
  stmtListNode->addChild(makeReadNode(2, "num2"));
  stmtListNode->addChild(makeReadNode(3, "num3"));
  procNode->addChild(std::move(stmtListNode));
  programNode->addChild(std::move(procNode));
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(*programNode, mockPKB, AbstractionType::FOLLOWS);

  unordered_map<int, set<int>> expected = {};
  expected[1] = {2, 3};
  expected[2] = {3};
  REQUIRE(mockPKB.isFollowsEqual(expected));
}

TEST_CASE("FollowsExtractor Simple Statement list with parser") {
  string input =
      "procedure simple {"
      "read num1;"
      "read num2;"
      "read num3;"
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::FOLLOWS);

  unordered_map<int, set<int>> expected = {};
  expected[1] = {2, 3};
  expected[2] = {3};
  REQUIRE(mockPKB.isFollowsEqual(expected));
}

TEST_CASE("FollowsExtractor with parser - if node") {
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
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::FOLLOWS);

  unordered_map<int, set<int>> expected = {};
  expected[1] = {2, 3};
  expected[2] = {3};
  REQUIRE(mockPKB.isFollowsEqual(expected));
}

TEST_CASE("FollowsExtractor with parser - if in while node") {
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
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::FOLLOWS);
  unordered_map<int, set<int>> expected = {};
  expected[1] = {2, 3, 8};
  expected[2] = {3, 8};
  expected[3] = {8};
  expected[4] = {7};
  REQUIRE(mockPKB.isFollowsEqual(expected));
}
