// TEMP_CATCH_INCLUDE
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../ast/TNodeUtils.h"
#include "ExtractorUtils.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/StmtListNode.h"

using std::unique_ptr, std::make_unique, std::vector, std::string,
    std::unordered_map, std::unordered_set;

TEST_CASE("CallsExtractor - no calls") {
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
  procNode->addChild(std::move(stmtListNode));
  programNode->addChild(std::move(procNode));
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(*programNode, mockPKB, AbstractionType::CALLS);

  unordered_map<string, std::unordered_set<string>> expected = {};
  REQUIRE(mockPKB.isCallsEqual(expected));
  REQUIRE(mockPKB.isCallsStarEqual(expected));
}

TEST_CASE("CallsExtractor with parser - no calls") {
  string input =
      "procedure simple {"
      "read num1;"
      "read num2;"
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CALLS);

  unordered_map<string, unordered_set<string>> expected = {};
  REQUIRE(mockPKB.isCallsEqual(expected));
  REQUIRE(mockPKB.isCallsStarEqual(expected));
}

TEST_CASE("CallsExtractor with parser - single calls") {
  string input =
      "procedure First {"
      "    call Second;"
      "}"
      "procedure Second {"
      "    read y;"
      "}";

  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CALLS);

  unordered_map<string, unordered_set<string>> expected = {};
  expected["First"] = {"Second"};
  REQUIRE(mockPKB.isCallsEqual(expected));
  REQUIRE(mockPKB.isCallsStarEqual(expected));
}

TEST_CASE("CallsExtractor with parser - multiple calls in one proc") {
  string input =
      "procedure First {"
      "    call Second;"
      "    read x;"
      "    call Third;"
      "}"
      "procedure Second {"
      "    read y;"
      "}"
      "procedure Third {"
      "    read z;"
      "}";

  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CALLS);

  unordered_map<string, unordered_set<string>> expected = {};
  expected["First"] = {"Second", "Third"};
  REQUIRE(mockPKB.isCallsEqual(expected));
  REQUIRE(mockPKB.isCallsStarEqual(expected));
}

TEST_CASE("CallsExtractor with parser - 2 chained calls") {
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
      "    read y;"
      "}";

  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CALLS);

  unordered_map<string, unordered_set<string>> expectedCalls = {};
  expectedCalls["First"] = {"Second"};
  expectedCalls["Second"] = {"Third"};
  REQUIRE(mockPKB.isCallsEqual(expectedCalls));
  unordered_map<string, unordered_set<string>> expectedCallsStar = {};
  expectedCallsStar["First"] = {"Second", "Third"};
  expectedCallsStar["Second"] = {"Third"};
  REQUIRE(mockPKB.isCallsStarEqual(expectedCallsStar));
}

TEST_CASE("CallsExtractor with parser - 2 chained calls from 1 procedure") {
  string input =
      "procedure One {"
      "    call Two;"
      "    call Three;"
      "    read i;"
      "}"
      "procedure Two {"
      "    call Four;"
      "    read j;"
      "}"
      "procedure Three {"
      "    call Four;"
      "    read k;"
      "}"
      "procedure Four {"
      "    read l;"
      "}";

  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CALLS);

  unordered_map<string, unordered_set<string>> expectedCalls = {};
  expectedCalls["One"] = {"Two", "Three"};
  expectedCalls["Two"] = {"Four"};
  expectedCalls["Three"] = {"Four"};
  REQUIRE(mockPKB.isCallsEqual(expectedCalls));
  unordered_map<string, unordered_set<string>> expectedCallsStar = {};
  expectedCallsStar["One"] = {"Two", "Three", "Four"};
  expectedCallsStar["Two"] = {"Four"};
  expectedCallsStar["Three"] = {"Four"};
  REQUIRE(mockPKB.isCallsStarEqual(expectedCallsStar));
}

TEST_CASE("CallsExtractor with parser - 3 chained calls") {
  string input =
      "procedure One {"
      "    call Two;"
      "    read i;"
      "}"
      "procedure Two {"
      "    call Three;"
      "    read j;"
      "}"
      "procedure Three {"
      "    call Four;"
      "    read k;"
      "}"
      "procedure Four {"
      "    read l;"
      "}";

  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CALLS);

  unordered_map<string, unordered_set<string>> expectedCalls = {};
  expectedCalls["One"] = {"Two"};
  expectedCalls["Two"] = {"Three"};
  expectedCalls["Three"] = {"Four"};
  REQUIRE(mockPKB.isCallsEqual(expectedCalls));
  unordered_map<string, unordered_set<string>> expectedCallsStar = {};
  expectedCallsStar["One"] = {"Two", "Three", "Four"};
  expectedCallsStar["Two"] = {"Three", "Four"};
  expectedCallsStar["Three"] = {"Four"};
  REQUIRE(mockPKB.isCallsStarEqual(expectedCallsStar));
}
