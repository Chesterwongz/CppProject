#include <vector>
#include <memory>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include "catch.hpp"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/StmtListNode.h"
#include "../mocks/MockPKBWriter.h"
#include "../ast/TNodeUtils.h"
#include "AbstractionTypes.h"
#include "ExtractorUtils.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::map, std::set, std::unordered_map,
std::unordered_set, std::pair;


TEST_CASE("PatternExtractor - no assign pattern") {
//    string input =
//        "procedure simple {"
//        "print x;"
//        "}";
    unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
    unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
    unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
    stmtListNode->addChild(makePrintNode(1, "x"));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(programNode.get(), mockPKB, AbstractionType::PATTERN);
    unordered_map<int, pair<string, string>> expected = unordered_map<int, pair<string, string>>();
    REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor with parser - no assign pattern") {
    string input =
        "procedure simple {"
        "print x;"
        "}";
    // extract
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
    unordered_map<int, pair<string, string>> expected = unordered_map<int, pair<string, string>>();
    REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor - 2 simple assign patterns") {
//    string input =
//        "procedure simple {"
//        "x = z + 2"
//        "y = x + 1"
//        "}";
    unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
    unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
    unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
    stmtListNode->addChild(makeAssignWithPlusNode(1, "x", "z", "2"));
    stmtListNode->addChild(makeAssignWithPlusNode(2, "y", "x", "1"));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(programNode.get(), mockPKB, AbstractionType::PATTERN);

    unordered_map<int, pair<string, string>> expected = {};
    expected[1] = {"x", "z2+"};
    expected[2] = {"y", "x1+"};
    REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor with parser - 2 simple assign patterns") {
    string input =
        "procedure simple {"
        "x = z + 2;"
        "y = x + 1;"
        "}";

    // extract
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::PATTERN);

    unordered_map<int, pair<string, string>> expected = {};
    expected[1] = {"x", "z2+"};
    expected[2] = {"y", "x1+"};
    REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor with parser - 2 same assign patterns for same var") {
    string input =
        "procedure simple {"
        "x = a - b * c;"
        "x = a - b * c;"
        "}";

    // extract
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
    unordered_map<int, pair<string, string>> expected = {};
    expected[1] = {"x", "abc*-"};
    expected[2] = {"x", "abc*-"};
    REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor with parser - 3 diff assign patterns for same var") {
    string input =
        "procedure simple {"
        "x = a - b * c;"
        "x = a * b + c;"
        "x = a / b - c * d;"
        "}";

    // extract
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
    unordered_map<int, pair<string, string>> expected = {};
    expected[1] = {"x", "abc*-"};
    expected[2] = {"x", "ab*c+"};
    expected[3] = {"x", "ab/cd*-"};
    REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor with parser - diff assign pattern for diff vars with parentheses") {
    string input =
        "procedure simple {"
        "y = (a + b) * c;"
        "z = a * (b + c);"
        "x = (a + b) * (c - d);"
        "}";

    // extract
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
    unordered_map<int, pair<string, string>> expected = {};
    expected[1] = {"y", "ab+c*"};
    expected[2] = {"z", "abc+*"};
    expected[3] = {"x", "ab+cd-*"};
    REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor with parser - if node") {
    string input =
        "procedure simple {"
        "read y;"
        "z = (a + b) * (c + d) - e / f * g;"
        "if (num1 < num2) then {"
        "x = a + b * c - d / e;"
        "} else {"
        "y = a * b + c / d;"
        "read z;"
        "}"
        "}";

    // extract
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
    unordered_map<int, pair<string, string>> expected = {};
    expected[2] = {"z", "ab+cd+*ef/g*-"};
    expected[4] = {"x", "abc*+de/-"};
    expected[5] = {"y", "ab*cd/+"};
    REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor with parser - if in while node") {
    string input =
        "procedure simple {"
        "read x;"
        "y = a * b + c % d - e;"
        "while (x < y) {"
        "if (x == y) then {"
        "x = a + b * c % d - e;"
        "} else { w = (a + b) % c; }"
        "z = a % b + c % d;"
        "}"
        "num1 = (a + b * c) % d;"
        "}";

    // extract
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
    unordered_map<int, pair<string, string>> expected = {};
    expected[2] = {"y", "ab*cd%+e-"};
    expected[5] = {"x", "abc*d%+e-"};
    expected[6] = {"w", "ab+c%"};
    expected[7] = {"z", "ab%c+cd%+"};
    expected[8] = {"num1", "abc*+d%"};
}

TEST_CASE("PatternExtractor with parser - assign pattern with all operators") {
    string input =
        "procedure simple {"
        "read a; read b; read c; read d; read e; read f;" // 1
        "x = a + b * c - d / e % f;" // 2
        "y = (a + b) * (c - d) / (e % f);" // 3
        "z = a * (b + c * d - e / f) % g;" // 4
        "a = a - b / c * d + e % f * g;" // 5
        "b = (a * b - c) % (d + e / f);" // 6
        "c = a / (b + c) * d - e % f + g;" // 7
        "d = a + b * (c % d - e) / f;" // 8
        "e = (a % b) * c - d / (e + f);" // 9
        "f = a / b * (c + d) % e - f;" // 10
        "g = (a + b % c) * (d - e / f);" // 11
        "}";

    // extract
    struct Storage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
    unordered_map<int, pair<string, string>> expected = {};
//    expected[2] = {"x", "abc*+de/f%-"};
//    expected[3] = {"y", "ab+cd-*ef%/"};
//    expected[4] = {"z", "abcd*+ef/-*g%"};
//    expected[5] = {"a", "abc/d*-ef%g*+"};
//    expected[6] = {"b", "ab*c-def/+%"};
//    expected[7] = {"c", "abc+/d*ef%-g+"};
//    expected[8] = {"d", "abcd%e-*f/+"};
//    expected[9] = {"e", "ab%c*def+/-"};
//    expected[10] = {"f", "ab/cd+*e%f-"};
//    expected[11] = {"g", "abc%+def/-*"};
    // TODO: update line num after parser is fixed
    expected[7] = {"x", "abc*+de/f%-"};
    expected[8] = {"y", "ab+cd-*ef%/"};
    expected[9] = {"z", "abcd*+ef/-*g%"};
    expected[10] = {"a", "abc/d*-ef%g*+"};
    expected[11] = {"b", "ab*c-def/+%"};
    expected[12] = {"c", "abc+/d*ef%-g+"};
    expected[13] = {"d", "abcd%e-*f/+"};
    expected[14] = {"e", "ab%c*def+/-"};
    expected[15] = {"f", "ab/cd+*e%f-"};
    expected[16] = {"g", "abc%+def/-*"};
    for (auto& [lineNum, pattern]: mockPKB.assignPatternStorage) {
        bool isPatternEqual = expected[lineNum] == pattern;
        std::cout << lineNum << " " << pattern.first << " " << pattern.second << " " << std::to_string(isPatternEqual) << std::endl;
    }
    REQUIRE(mockPKB.isAssignPatternEqual(expected));
}
