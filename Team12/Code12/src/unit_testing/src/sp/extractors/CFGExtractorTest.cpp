#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "catch.hpp"
#include "sp/ast/ProgramNode.h"
#include "ExtractorUtils.h"
#include "../mocks/MockCFG.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::unordered_map, std::unordered_set;

TEST_CASE("CFGExtractor - 1 procedure with no nesting") {
    string input =
        "procedure simple {"
        "read num1;"
        "read num2;"
        "}";
    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::CFG);

    unordered_map<int, vector<int>> expectedCfg = {
        {1, {2}},
        {2, {common::CFG_END_STMT_NUM}}
    };
    unordered_map<string, unique_ptr<CFG>> expected;
    expected.emplace("simple", std::make_unique<MockCFG>(expectedCfg));
    REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - 1 procedure with a while loop") {
    string input =
        "procedure simpleLoop {"
        "   read m;" // 1
        "   while (m < 5) {" // 2
        "       print m;" // 3
        "       read n;" // 4
        "   }"
        "   print n;" // 5
        "}";
    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::CFG);

    unordered_map<int, vector<int>> expectedCfg = {
        {1, {2}},
        {2, {3, 5}},
        {3, {4}},
        {4, {2}},
        {5, {common::CFG_END_STMT_NUM}}
    };
    unordered_map<string, unique_ptr<CFG>> expected;
    expected.emplace("simpleLoop", std::make_unique<MockCFG>(expectedCfg));
    REQUIRE(mockPKB.isCFGEqual(expected));
}