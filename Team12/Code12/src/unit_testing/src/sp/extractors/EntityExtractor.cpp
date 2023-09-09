#include <vector>
#include <memory>
#include <map>
#include <set>
#include <unordered_set>
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

using std::unique_ptr, std::make_unique, std::vector, std::string, std::map, std::set, std::unordered_set;

unordered_set<string> getVariables(DesignExtractor* designExtractor) {
    return designExtractor->getVariables();
}

unordered_set<string> getConstants(DesignExtractor* designExtractor) {
    return designExtractor->getConstants();
}

unordered_set<string> getProcedures(DesignExtractor* designExtractor) {
    return designExtractor->getProcedures();
}

unordered_set<int> getAssignStmts(DesignExtractor* designExtractor) {
    return designExtractor->getAssignStmts();
}

unordered_set<int> getCallStmts(DesignExtractor* designExtractor) {
    return designExtractor->getCallStmts();
}

unordered_set<int> getIfStmts(DesignExtractor* designExtractor) {
    return designExtractor->getIfStmts();
}

unordered_set<int> getPrintStmts(DesignExtractor* designExtractor) {
    return designExtractor->getPrintStmts();
}

unordered_set<int> getReadStmts(DesignExtractor* designExtractor) {
    return designExtractor->getReadStmts();
}

unordered_set<int> getWhileStmts(DesignExtractor* designExtractor) {
    return designExtractor->getWhileStmts();
}

unique_ptr<ReadNode> makeReadNodeInEntity(int lineNum, const string& varName) {
    unique_ptr<ReadNode> readNode = make_unique<ReadNode>(lineNum);
    readNode->addChild(make_unique<VarNode>(varName));
    return readNode;
}

unique_ptr<PrintNode> makePrintNodeInEntity(int lineNum, const string& varName) {
    unique_ptr<PrintNode> printNode = make_unique<PrintNode>(lineNum);
    printNode->addChild(make_unique<VarNode>(varName));
    return printNode;
}

unique_ptr<AssignNode> makeAssignNodeInEntity(int lineNum) {
    unique_ptr<AssignNode> assignNode = make_unique<AssignNode>(lineNum);
    assignNode->addChild(make_unique<VarNode>("x"));
    unique_ptr<PlusNode> plusNode = make_unique<PlusNode>(
        make_unique<VarNode>("y"),
        make_unique<ConstNode>("1")
    );
    assignNode->addChild(std::move(plusNode));
    return assignNode;
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
    stmtListNode->addChild(makeReadNodeInEntity(1, "y"));
    stmtListNode->addChild(makeReadNodeInEntity(2, "y"));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());

    REQUIRE(getVariables(&designExtractor) == unordered_set<string>{"y"});
    REQUIRE(getConstants(&designExtractor).empty());
    REQUIRE(getProcedures(&designExtractor) == unordered_set<string>{"simple"});
    REQUIRE(getAssignStmts(&designExtractor).empty());
    REQUIRE(getCallStmts(&designExtractor).empty());
    REQUIRE(getIfStmts(&designExtractor).empty());
    REQUIRE(getPrintStmts(&designExtractor).empty());
    REQUIRE(getReadStmts(&designExtractor) == unordered_set<int>{1, 2});
    REQUIRE(getWhileStmts(&designExtractor).empty());
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
    stmtListNode->addChild(makeReadNodeInEntity(1, "y"));
    stmtListNode->addChild(makePrintNodeInEntity(2, "x"));
    stmtListNode->addChild(makeAssignNodeInEntity(3));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());

    REQUIRE(getVariables(&designExtractor) == unordered_set<string>{"x", "y"});
    REQUIRE(getConstants(&designExtractor) == unordered_set<string>{"1"});
    REQUIRE(getProcedures(&designExtractor) == unordered_set<string>{"simple"});
    REQUIRE(getAssignStmts(&designExtractor) == unordered_set<int>{3});
    REQUIRE(getCallStmts(&designExtractor).empty());
    REQUIRE(getIfStmts(&designExtractor).empty());
    REQUIRE(getPrintStmts(&designExtractor) == unordered_set<int>{2});
    REQUIRE(getReadStmts(&designExtractor) == unordered_set<int>{1});
    REQUIRE(getWhileStmts(&designExtractor).empty());
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
    stmtListNode->addChild(makeReadNodeInEntity(1, "y"));
    stmtListNode->addChild(makePrintNodeInEntity(2, "x"));
    // make if node
    unique_ptr<IfNode> ifNode = make_unique<IfNode>(3);
    ifNode->addChild(make_unique<LtNode>(make_unique<VarNode>("num1"), make_unique<VarNode>("num2")));
    unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
    thenStmtListNode->addChild(makePrintNodeInEntity(4, "z"));
    ifNode->addChild(std::move(thenStmtListNode));
    unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
    elseStmtListNode->addChild(makeAssignNodeInEntity(5));
    ifNode->addChild(std::move(elseStmtListNode));
    // add if to proc
    stmtListNode->addChild(std::move(ifNode));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());

    REQUIRE(getVariables(&designExtractor) == unordered_set<string>{"x", "y", "z", "num1", "num2"});
    REQUIRE(getConstants(&designExtractor) == unordered_set<string>{"1"});
    REQUIRE(getProcedures(&designExtractor) == unordered_set<string>{"simple"});
    REQUIRE(getAssignStmts(&designExtractor) == unordered_set<int>{5});
    REQUIRE(getCallStmts(&designExtractor).empty());
    REQUIRE(getIfStmts(&designExtractor) == unordered_set<int>{3});
    REQUIRE(getPrintStmts(&designExtractor) == unordered_set<int>{2, 4});
    REQUIRE(getReadStmts(&designExtractor) == unordered_set<int>{1});
    REQUIRE(getWhileStmts(&designExtractor).empty());
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
    stmtListNode->addChild(makeReadNodeInEntity(1, "x"));
    stmtListNode->addChild(makeReadNodeInEntity(2, "y"));
    // make while node
    unique_ptr<WhileNode> whileNode = make_unique<WhileNode>(3);
    whileNode->addChild(make_unique<LtNode>(make_unique<VarNode>("x"), make_unique<VarNode>("y")));
    unique_ptr<StmtListNode> whileStmtListNode = make_unique<StmtListNode>();
    // make if node
    unique_ptr<IfNode> ifNode = make_unique<IfNode>(4);
    ifNode->addChild(make_unique<EqNode>(make_unique<VarNode>("x"), make_unique<VarNode>("y")));
    unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
    thenStmtListNode->addChild(makeAssignNodeInEntity(5));
    ifNode->addChild(std::move(thenStmtListNode));
    unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
    elseStmtListNode->addChild(makePrintNodeInEntity(6, "w"));
    ifNode->addChild(std::move(elseStmtListNode));
    // add if to while
    whileStmtListNode->addChild(std::move(ifNode));
    whileStmtListNode->addChild(makePrintNodeInEntity(7, "z"));
    // add while to proc
    whileNode->addChild(std::move(whileStmtListNode));
    stmtListNode->addChild(std::move(whileNode));
    stmtListNode->addChild(makeReadNodeInEntity(8, "num1"));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());

    REQUIRE(getVariables(&designExtractor) == unordered_set<string>{"x", "y", "w", "z", "num1"});
    REQUIRE(getConstants(&designExtractor) == unordered_set<string>{"1"});
    REQUIRE(getProcedures(&designExtractor) == unordered_set<string>{"simple"});
    REQUIRE(getAssignStmts(&designExtractor) == unordered_set<int>{5});
    REQUIRE(getCallStmts(&designExtractor).empty());
    REQUIRE(getIfStmts(&designExtractor) == unordered_set<int>{4});
    REQUIRE(getPrintStmts(&designExtractor) == unordered_set<int>{6, 7});
    REQUIRE(getReadStmts(&designExtractor) == unordered_set<int>{1, 2, 8});
    REQUIRE(getWhileStmts(&designExtractor) == unordered_set<int>{3});
}
