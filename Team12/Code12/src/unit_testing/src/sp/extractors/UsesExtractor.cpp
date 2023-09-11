#include <vector>
#include <memory>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "catch.hpp"
#include "sp/extractors/DesignExtractor.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/StmtListNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "../mocks/MockPKBWriter.h"
#include "../ast/TNodeUtils.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::map, std::set, std::unordered_map, std::unordered_set;

void extractUses(TNode* node, MockPKBWriter &mockPKBWriter) {
    Populator populator;
    std::vector<std::unique_ptr<Extractor>> extractors;
    extractors.emplace_back(make_unique<UsesExtractor>(&mockPKBWriter));
    populator.populate(node, extractors);
}

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
    MockPKBWriter mockPKB;
    extractUses(programNode.get(), mockPKB);
    unordered_map<string, unordered_set<int>> expected = {};
    REQUIRE(mockPKB.isUsesEqual(expected));
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
    MockPKBWriter mockPKB;
    extractUses(programNode.get(), mockPKB);
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
    MockPKBWriter mockPKB;
    extractUses(programNode.get(), mockPKB);
    unordered_map<string, unordered_set<int>> expected = {};
    expected["x"] = {2};
    expected["y"] = {3, 5};
    expected["z"] = {3, 4};
    expected["num1"] = {3};
    expected["num2"] = {3};
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
    MockPKBWriter mockPKB;
    extractUses(programNode.get(), mockPKB);
    unordered_map<string, unordered_set<int>> expected = {};
    expected["x"] = {3, 4};
    expected["y"] = {3, 4, 5};
    expected["w"] = {3, 4, 6};
    expected["z"] = {3, 7};
    REQUIRE(mockPKB.isUsesEqual(expected));
}