#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

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

  unordered_map<string, vector<pair<int, string>>> expected = {};
  REQUIRE(mockPKB.isCallsEqual(expected));
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

  unordered_map<string, vector<pair<int, string>>> expected = {};
  REQUIRE(mockPKB.isCallsEqual(expected));
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

  unordered_map<string, vector<pair<int, string>>> expected = {};
  expected["First"] = {std::make_pair(1, "Second")};
  REQUIRE(mockPKB.isCallsEqual(expected));
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

  unordered_map<string, vector<pair<int, string>>> expected = {};
  expected["First"] = {
      std::make_pair(1, "Second"),
      std::make_pair(3, "Third"),
  };
  REQUIRE(mockPKB.isCallsEqual(expected));
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

  unordered_map<string, vector<pair<int, string>>> expected = {};
  expected["First"] = {std::make_pair(1, "Second")};
  expected["Second"] = {std::make_pair(3, "Third")};
  REQUIRE(mockPKB.isCallsEqual(expected));
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

  unordered_map<string, vector<pair<int, string>>> expected = {};
  expected["One"] = {std::make_pair(1, "Two"), std::make_pair(2, "Three")};
  expected["Two"] = {std::make_pair(4, "Four")};
  expected["Three"] = {std::make_pair(6, "Four")};
  REQUIRE(mockPKB.isCallsEqual(expected));
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

  unordered_map<string, vector<pair<int, string>>> expected = {};
  expected["One"] = {std::make_pair(1, "Two")};
  expected["Two"] = {std::make_pair(3, "Three")};
  expected["Three"] = {std::make_pair(5, "Four")};
  REQUIRE(mockPKB.isCallsEqual(expected));
}
