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
#include "sp/ast/statements/PrintNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/ast/statements/AssignNode.h"
#include "sp/ast/expressions/VarNode.h"
#include "sp/ast/expressions/ConstNode.h"
#include "sp/ast/expressions/arithmetic/PlusNode.h"
#include "sp/ast/expressions/relational/LtNode.h"
#include "sp/ast/expressions/relational/EqNode.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::map, std::set;

map<string, set<int>> getUsesMap(DesignExtractor* designExtractor) {
    return designExtractor->getUsesMap();
}

void printUsesMap(const map<string, set<int>>& map) {
    for (const auto& elem : map) {
        std::cout << elem.first << ": ";
        for (const auto &follows : elem.second) {
            std::cout << follows << " ";
        }
        std::cout << "\n";
    }
}

unique_ptr<ReadNode> makeReadNodeInUses(int lineNum, const string& varName) {
    unique_ptr<ReadNode> readNode = make_unique<ReadNode>(lineNum);
    readNode->addChild(make_unique<VarNode>(varName));
    return readNode;
}

unique_ptr<PrintNode> makePrintNodeInUses(int lineNum, const string& varName) {
    unique_ptr<PrintNode> printNode = make_unique<PrintNode>(lineNum);
    printNode->addChild(make_unique<VarNode>(varName));
    return printNode;
}

unique_ptr<AssignNode> makeAssignNodeInParent(int lineNum) {
    unique_ptr<AssignNode> assignNode = make_unique<AssignNode>(lineNum);
    assignNode->addChild(make_unique<VarNode>("x"));
    unique_ptr<PlusNode> plusNode = make_unique<PlusNode>(
        make_unique<VarNode>("y"),
       make_unique<ConstNode>("1")
    );
    assignNode->addChild(std::move(plusNode));
    return assignNode;
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
    stmtListNode->addChild(makeReadNodeInUses(1, "y"));
    stmtListNode->addChild(makeReadNodeInUses(2, "y"));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());

    // get follows map
    map<string, set<int>> res = getUsesMap(&designExtractor);
    printUsesMap(res);
    REQUIRE(res.empty());
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
    stmtListNode->addChild(makeReadNodeInUses(1, "y"));
    stmtListNode->addChild(makePrintNodeInUses(2, "x"));
    stmtListNode->addChild(makeAssignNodeInParent(3));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());

    // get follows map
    map<string, set<int>> res = getUsesMap(&designExtractor);
    printUsesMap(res);
    REQUIRE(res.size() == 2);
    REQUIRE(res["x"] == set<int>{2});
    REQUIRE(res["y"] == set<int>{3});
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
    stmtListNode->addChild(makeReadNodeInUses(1, "y"));
    stmtListNode->addChild(makePrintNodeInUses(2, "x"));
    // make if node
    unique_ptr<IfNode> ifNode = make_unique<IfNode>(3);
    ifNode->addChild(make_unique<LtNode>(make_unique<VarNode>("num1"), make_unique<VarNode>("num2")));
    unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
    thenStmtListNode->addChild(makePrintNodeInUses(4, "z"));
    ifNode->addChild(std::move(thenStmtListNode));
    unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
    elseStmtListNode->addChild(makeAssignNodeInParent(5));
    ifNode->addChild(std::move(elseStmtListNode));
    // add if to proc
    stmtListNode->addChild(std::move(ifNode));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());
    auto res = getUsesMap(&designExtractor);
    printUsesMap(res);
    REQUIRE(res.size() == 5);
    REQUIRE(res["x"] == set<int>{2});
    REQUIRE(res["y"] == set<int>{3, 5});
    REQUIRE(res["z"] == set<int>{3, 4});
    REQUIRE(res["num1"] == set<int>{3});
    REQUIRE(res["num2"] == set<int>{3});
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
    stmtListNode->addChild(makeReadNodeInUses(1, "x"));
    stmtListNode->addChild(makeReadNodeInUses(2, "y"));
    // make while node
    unique_ptr<WhileNode> whileNode = make_unique<WhileNode>(3);
    whileNode->addChild(make_unique<LtNode>(make_unique<VarNode>("x"), make_unique<VarNode>("y")));
    unique_ptr<StmtListNode> whileStmtListNode = make_unique<StmtListNode>();
    // make if node
    unique_ptr<IfNode> ifNode = make_unique<IfNode>(4);
    ifNode->addChild(make_unique<EqNode>(make_unique<VarNode>("x"), make_unique<VarNode>("y")));
    unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
    thenStmtListNode->addChild(makeAssignNodeInParent(5));
    ifNode->addChild(std::move(thenStmtListNode));
    unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
    elseStmtListNode->addChild(makePrintNodeInUses(6, "w"));
    ifNode->addChild(std::move(elseStmtListNode));
    // add if to while
    whileStmtListNode->addChild(std::move(ifNode));
    whileStmtListNode->addChild(makePrintNodeInUses(7, "z"));
    // add while to proc
    whileNode->addChild(std::move(whileStmtListNode));
    stmtListNode->addChild(std::move(whileNode));
    stmtListNode->addChild(makeReadNodeInUses(8, "num1"));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());
    auto res = getUsesMap(&designExtractor);
    printUsesMap(res);
    REQUIRE(res.size() == 4);
    REQUIRE(res["x"] == set<int>{3, 4});
    REQUIRE(res["y"] == set<int>{3, 4, 5});
    REQUIRE(res["w"] == set<int>{6, 4, 3});
    REQUIRE(res["z"] == set<int>{7, 3});
}