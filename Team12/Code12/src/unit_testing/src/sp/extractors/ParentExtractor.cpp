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

void extractParent(TNode* node, MockPKBWriter &mockPKBWriter) {
    Populator populator;
    std::vector<std::unique_ptr<Extractor>> extractors;
    extractors.emplace_back(make_unique<ParentExtractor>(&mockPKBWriter));
    populator.populate(node, extractors);
}

TEST_CASE("ParentExtractor - no parent") {
//    string input =
//        "procedure simple {"
//        "read num1;"
//        "read num2;"
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
    MockPKBWriter mockPkbWriter;
    extractParent(programNode.get(), mockPkbWriter);

    REQUIRE(mockPkbWriter.isParentEqual({}));
}

TEST_CASE("ParentExtractor - if node") {
//    string input =
//        "procedure simple {"
// 1       "read num1;"
// 2       "read num2;"
// 3       "if (num1 < num2) then {"
// 4       "read"
// 5       "read"
//        "} else {"
// 6       "read"
// 7       "read"
//        "}"
//        "}";
    unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
    unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
    unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
    stmtListNode->addChild(makeReadNode(1, "num1"));
    stmtListNode->addChild(makeReadNode(2, "num2"));
    // make if node
    unique_ptr<IfNode> ifNode = make_unique<IfNode>(3);
    unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
    thenStmtListNode->addChild(makeReadNode(4, "num1"));
    thenStmtListNode->addChild(makeReadNode(5, "num2"));
    ifNode->addChild(std::move(thenStmtListNode));
    unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
    elseStmtListNode->addChild(makeReadNode(6, "num1"));
    elseStmtListNode->addChild(makeReadNode(7, "num2"));
    ifNode->addChild(std::move(elseStmtListNode));
    // add if to proc
    stmtListNode->addChild(std::move(ifNode));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    MockPKBWriter mockPkbWriter;
    extractParent(programNode.get(), mockPkbWriter);
    unordered_map<int, set<int>> expected = {};
    expected[3] = {4, 5, 6, 7};
    REQUIRE(mockPkbWriter.isParentEqual(expected));
}

TEST_CASE("ParentExtractor - while node") {
//    string input =
//        "procedure simple {"
//        "read"
//        "read"
//        "while (num1 < num2) {"
//        "if (num1 == num2) then {"
//        "read"
//        "} else { read x; }"
//        "read"
//        "}"
//        "read"
//        "}";
    unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
    unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
    unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
    stmtListNode->addChild(makeReadNode(1, "x"));
    stmtListNode->addChild(makeReadNode(2, "x"));
    // make while node
    unique_ptr<WhileNode> whileNode = make_unique<WhileNode>(3);
    unique_ptr<StmtListNode> whileStmtListNode = make_unique<StmtListNode>();
    // make if node
    unique_ptr<IfNode> ifNode = make_unique<IfNode>(4);
    unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
    thenStmtListNode->addChild(makeReadNode(5, "x"));
    ifNode->addChild(std::move(thenStmtListNode));
    unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
    elseStmtListNode->addChild(makeReadNode(6, "x"));
    ifNode->addChild(std::move(elseStmtListNode));
    // add if to while
    whileStmtListNode->addChild(std::move(ifNode));
    whileStmtListNode->addChild(makeReadNode(7, "x"));
    // add while to proc
    whileNode->addChild(std::move(whileStmtListNode));
    stmtListNode->addChild(std::move(whileNode));
    stmtListNode->addChild(makeReadNode(8, "x"));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    MockPKBWriter mockPkbWriter;
    extractParent(programNode.get(), mockPkbWriter);

    unordered_map<int, set<int>> expected = {};
    expected[3] = {4, 5, 6, 7};
    expected[4] = {5, 6};
    REQUIRE(mockPkbWriter.isParentEqual(expected));
}