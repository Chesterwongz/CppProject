#include <vector>
#include <memory>
#include <map>
#include <set>
#include <iostream>
#include "catch.hpp"
#include "sp/extractors/DesignExtractor.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/StmtListNode.h"
#include "sp/ast/statements/ReadNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::map, std::set;

map<int, set<int>> getParentMap(DesignExtractor* designExtractor) {
    return designExtractor->getParentMap();
}

void printParentMap(const map<int, set<int>>& followsMap) {
    for (const auto& elem : followsMap) {
        std::cout << elem.first << ": ";
        for (const auto &follows : elem.second) {
            std::cout << follows << " ";
        }
        std::cout << "\n";
    }
}

unique_ptr<ReadNode> makeReadNodeInParent(int lineNum) {
    return make_unique<ReadNode>(lineNum);
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
    stmtListNode->addChild(makeReadNodeInParent(1));
    stmtListNode->addChild(makeReadNodeInParent(2));
    stmtListNode->addChild(makeReadNodeInParent(3));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());

    // get follows map
    map<int, set<int>> res = getParentMap(&designExtractor);
    printParentMap(res);
    REQUIRE(res.empty());
}

TEST_CASE("ParentExtractor - if node") {
//    string input =
//        "procedure simple {"
//        "read num1;"
//        "read num2;"
//        "if (num1 < num2) then {"
//        "read"
//        "read"
//        "} else {"
//        "read"
//        "read"
//        "}"
//        "}";
    unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
    unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
    unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
    stmtListNode->addChild(makeReadNodeInParent(1));
    stmtListNode->addChild(makeReadNodeInParent(2));
    // make if node
    unique_ptr<IfNode> ifNode = make_unique<IfNode>(3);
    unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
    thenStmtListNode->addChild(makeReadNodeInParent(4));
    thenStmtListNode->addChild(makeReadNodeInParent(5));
    ifNode->addChild(std::move(thenStmtListNode));
    unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
    elseStmtListNode->addChild(makeReadNodeInParent(6));
    elseStmtListNode->addChild(makeReadNodeInParent(7));
    ifNode->addChild(std::move(elseStmtListNode));
    // add if to proc
    stmtListNode->addChild(std::move(ifNode));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());
    auto res = getParentMap(&designExtractor);
    printParentMap(res);
    REQUIRE(res.size() == 1);
    REQUIRE(res[3] == set<int>{4, 5, 6, 7});
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
    stmtListNode->addChild(makeReadNodeInParent(1));
    stmtListNode->addChild(makeReadNodeInParent(2));
    // make while node
    unique_ptr<WhileNode> whileNode = make_unique<WhileNode>(3);
    unique_ptr<StmtListNode> whileStmtListNode = make_unique<StmtListNode>();
    // make if node
    unique_ptr<IfNode> ifNode = make_unique<IfNode>(4);
    unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
    thenStmtListNode->addChild(makeReadNodeInParent(5));
    ifNode->addChild(std::move(thenStmtListNode));
    unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
    elseStmtListNode->addChild(makeReadNodeInParent(6));
    ifNode->addChild(std::move(elseStmtListNode));
    // add if to while
    whileStmtListNode->addChild(std::move(ifNode));
    whileStmtListNode->addChild(makeReadNodeInParent(7));
    // add while to proc
    whileNode->addChild(std::move(whileStmtListNode));
    stmtListNode->addChild(std::move(whileNode));
    stmtListNode->addChild(makeReadNodeInParent(8));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());
    auto res = getParentMap(&designExtractor);
    printParentMap(res);
    REQUIRE(res.size() == 2);
    REQUIRE(res[3] == set<int>{4, 5, 6, 7});
    REQUIRE(res[4] == set<int>{5, 6});
}