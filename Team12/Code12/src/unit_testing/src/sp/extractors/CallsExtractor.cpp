#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "catch.hpp"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/StmtListNode.h"
#include "../ast/TNodeUtils.h"
#include "ExtractorUtils.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::unordered_map, std::unordered_set;

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
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(programNode.get(), mockPKB, AbstractionType::CALLS);

    unordered_map<string, std::unordered_set<string>> expected = {};
    REQUIRE(mockPKB.isCallsEqual(expected));
}

TEST_CASE("CallsExtractor with parser - no calls") {
    string input =
        "procedure simple {"
        "read num1;"
        "read num2;"
        "}";
    // extract
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::CALLS);

    unordered_map<string, unordered_set<string>> expected = {};
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
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::CALLS);

    unordered_map<string, unordered_set<string>> expected = {};
    expected["First"] = {"Second"};
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
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::CALLS);

    unordered_map<string, unordered_set<string>> expected = {};
    expected["First"] = {"Second", "Third"};
    REQUIRE(mockPKB.isCallsEqual(expected));
}

TEST_CASE("CallsExtractor with parser - chained calls") {
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
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::CALLS);

    unordered_map<string, unordered_set<string>> expected = {};
    expected["First"] = {"Second"};
    expected["Second"] = {"Third"};
    REQUIRE(mockPKB.isCallsEqual(expected));
}
