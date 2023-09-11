#include <vector>
#include <memory>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "catch.hpp"
#include "sp/extractors/DesignExtractor.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/StmtListNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "../mocks/MockPKBWriter.h"
#include "../ast/TNodeUtils.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::map, std::set, std::unordered_set, std::unordered_map;

void extractEntity(TNode* node, MockPKBWriter &mockPKBWriter) {
    Populator populator;
    std::vector<std::unique_ptr<Extractor>> extractors;
    extractors.emplace_back(make_unique<EntityExtractor>(&mockPKBWriter));
    populator.populate(node, extractors);
}

TEST_CASE("EntityExtractor - only reads") {
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
    extractEntity(programNode.get(), mockPKB);

    // compare test results
    REQUIRE(mockPKB.isConstantsEqual({}));
    REQUIRE(mockPKB.isVariablesEqual({"y"}));
    REQUIRE(mockPKB.isProceduresEqual({{"simple", 1}}));
    REQUIRE(mockPKB.isAssignsEqual({}));
    REQUIRE(mockPKB.isCallsEqual({}));
    REQUIRE(mockPKB.isIfsEqual({}));
    REQUIRE(mockPKB.isPrintsEqual({}));
    REQUIRE(mockPKB.isReadsEqual({1, 2}));
    REQUIRE(mockPKB.isWhilesEqual({}));
}

TEST_CASE("EntityExtractor - non-nesting, 1 uses") {
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
    extractEntity(programNode.get(), mockPKB);

    REQUIRE(mockPKB.isConstantsEqual({"1"}));
    REQUIRE(mockPKB.isVariablesEqual({"x", "y"}));
    REQUIRE(mockPKB.isProceduresEqual({{"simple", 1}}));
    REQUIRE(mockPKB.isAssignsEqual({3}));
    REQUIRE(mockPKB.isCallsEqual({}));
    REQUIRE(mockPKB.isIfsEqual({}));
    REQUIRE(mockPKB.isPrintsEqual({2}));
    REQUIRE(mockPKB.isReadsEqual({1}));
    REQUIRE(mockPKB.isWhilesEqual({}));
}

TEST_CASE("EntityExtractor - if node") {
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
    extractEntity(programNode.get(), mockPKB);

    REQUIRE(mockPKB.isConstantsEqual({"1"}));
    REQUIRE(mockPKB.isVariablesEqual({"x", "y", "z", "num1", "num2"}));
    REQUIRE(mockPKB.isProceduresEqual({{"simple", 1}}));
    REQUIRE(mockPKB.isAssignsEqual({5}));
    REQUIRE(mockPKB.isCallsEqual({}));
    REQUIRE(mockPKB.isIfsEqual({3}));

    REQUIRE(mockPKB.isPrintsEqual({2, 4}));
    REQUIRE(mockPKB.isReadsEqual({1}));
    REQUIRE(mockPKB.isWhilesEqual({}));
}

TEST_CASE("EntityExtractor - if in while node") {
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
    extractEntity(programNode.get(), mockPKB);

    REQUIRE(mockPKB.isConstantsEqual({"1"}));
    REQUIRE(mockPKB.isVariablesEqual({"x", "y", "w", "z", "num1"}));
    REQUIRE(mockPKB.isProceduresEqual({{"simple", 1}}));
    REQUIRE(mockPKB.isAssignsEqual({5}));
    REQUIRE(mockPKB.isCallsEqual({}));
    REQUIRE(mockPKB.isIfsEqual({4}));
    REQUIRE(mockPKB.isPrintsEqual({6, 7}));
    REQUIRE(mockPKB.isReadsEqual({1, 2, 8}));
    REQUIRE(mockPKB.isWhilesEqual({3}));
}
