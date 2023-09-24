#include <vector>
#include <memory>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "catch.hpp"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/StmtListNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/ast/terminals/VarNode.h"
#include "sp/ast/expressions/relational/LtNode.h"
#include "sp/ast/expressions/relational/EqNode.h"
#include "../mocks/MockPKBWriter.h"
#include "../ast/TNodeUtils.h"
#include "AbstractionTypes.h"
#include "ExtractorUtils.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::map, std::set, std::unordered_map, std::unordered_set;

TEST_CASE("ModifiesExtractor - no modifies") {
//    string input =
//        "procedure simple {"
//        "print x;"
//        "print y;"
//        "}";
    unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
    unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
    unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
    stmtListNode->addChild(makePrintNode(1, "x"));
    stmtListNode->addChild(makePrintNode(2, "y"));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(*programNode, mockPKB, AbstractionType::MODIFIES);
    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = unordered_map<string, unordered_set<int>>();
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}

TEST_CASE("ModifiesExtractor with parser - no modifies") {
    string input =
        "procedure simple {"
        "print x;"
        "print y;"
        "}";
    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::MODIFIES);
    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = unordered_map<string, unordered_set<int>>();
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}

TEST_CASE("ModifiesExtractor - 2 read modifies") {
//    string input =
//        "procedure simple {"
//        "read x;"
//        "read y;"
//        "}";
    unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
    unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
    unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
    stmtListNode->addChild(makeReadNode(1, "x"));
    stmtListNode->addChild(makeReadNode(2, "y"));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(*programNode, mockPKB, AbstractionType::MODIFIES);

    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
    expectedVarToStmtNum["x"] = {1};
    expectedVarToStmtNum["y"] = {2};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    expectedVarToProcName["x"] = {"simple"};
    expectedVarToProcName["y"] = {"simple"};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}

TEST_CASE("ModifiesExtractor with parser - 2 read modifies") {
    string input =
        "procedure simple {"
        "read x;"
        "read y;"
        "}";

    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::MODIFIES);

    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
    expectedVarToStmtNum["x"] = {1};
    expectedVarToStmtNum["y"] = {2};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    expectedVarToProcName["x"] = {"simple"};
    expectedVarToProcName["y"] = {"simple"};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}

TEST_CASE("ModifiesExtractor - 1 read 1 assign") {
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
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(*programNode, mockPKB, AbstractionType::MODIFIES);
    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
    expectedVarToStmtNum["x"] = {3};
    expectedVarToStmtNum["y"] = {1};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    expectedVarToProcName["x"] = {"simple"};
    expectedVarToProcName["y"] = {"simple"};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}

TEST_CASE("ModifiesExtractor with parser - 1 read 1 assign") {
    string input =
        "procedure simple {"
        "read y;"
        "print x;"
        "x = y + 1;"
        "}";

    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::MODIFIES);
    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
    expectedVarToStmtNum["x"] = {3};
    expectedVarToStmtNum["y"] = {1};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    expectedVarToProcName["x"] = {"simple"};
    expectedVarToProcName["y"] = {"simple"};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}

TEST_CASE("ModifiesExtractor - if node") {
//    string input =
//        "procedure simple {"
// 1       "read y;"
// 2       "print x;"
// 3       "if (num1 < num2) then {"
// 4       "read z;"
//        "} else {"
// 5       "x = y + 1;"
// 6       "read z;"
//        "}"
//        "}";
    unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
    unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
    unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
    stmtListNode->addChild(makeReadNode(1, "y"));
    stmtListNode->addChild(makePrintNode(2, "x"));
    // make if node
    unique_ptr<IfNode> ifNode = make_unique<IfNode>(3);
    ifNode->addChild(make_unique<LtNode>(make_unique<VarNode>("num1"), make_unique<VarNode>("num2")));
    unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
    thenStmtListNode->addChild(makeReadNode(4, "z"));
    ifNode->addChild(std::move(thenStmtListNode));
    unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
    elseStmtListNode->addChild(makeAssignWithPlusNode(5, "x", "y", "1"));
    elseStmtListNode->addChild(makeReadNode(6, "z"));
    ifNode->addChild(std::move(elseStmtListNode));
    // add if to proc
    stmtListNode->addChild(std::move(ifNode));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));

    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(*programNode, mockPKB, AbstractionType::MODIFIES);
    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
    expectedVarToStmtNum["x"] = {3, 5};
    expectedVarToStmtNum["y"] = {1};
    expectedVarToStmtNum["z"] = {3, 4, 6};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    expectedVarToProcName["x"] = {"simple"};
    expectedVarToProcName["y"] = {"simple"};
    expectedVarToProcName["z"] = {"simple"};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}

TEST_CASE("ModifiesExtractor with parser - if node") {
    string input =
        "procedure simple {"
        "read y;"
        "print x;"
        "if (num1 < num2) then {"
        "read z;"
        "} else {"
        "x = y + 1;"
        "read z;"
        "}"
        "}";

    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::MODIFIES);
    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
    expectedVarToStmtNum["x"] = {3, 5};
    expectedVarToStmtNum["y"] = {1};
    expectedVarToStmtNum["z"] = {3, 4, 6};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    expectedVarToProcName["x"] = {"simple"};
    expectedVarToProcName["y"] = {"simple"};
    expectedVarToProcName["z"] = {"simple"};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}

TEST_CASE("ModifiesExtractor - if in while node") {
//    string input =
//        "procedure simple {"
// 1       "read x"
// 2       "read y"
// 3       "while (x < y) {"
// 4       "if (x == y) then {"
// 5       "x = y + 1;"
// 6       "} else { read w; }"
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
    whileNode->addChild(make_unique<LtNode>(make_unique<VarNode>("x"), make_unique<VarNode>("y")));
    unique_ptr<StmtListNode> whileStmtListNode = make_unique<StmtListNode>();
    // make if node
    unique_ptr<IfNode> ifNode = make_unique<IfNode>(4);
    ifNode->addChild(make_unique<EqNode>(make_unique<VarNode>("x"), make_unique<VarNode>("y")));
    unique_ptr<StmtListNode> thenStmtListNode = make_unique<StmtListNode>();
    thenStmtListNode->addChild(makeAssignWithPlusNode(5, "x", "y", "1"));
    ifNode->addChild(std::move(thenStmtListNode));
    unique_ptr<StmtListNode> elseStmtListNode = make_unique<StmtListNode>();
    elseStmtListNode->addChild(makeReadNode(6, "w"));
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
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(*programNode, mockPKB, AbstractionType::MODIFIES);
    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
    expectedVarToStmtNum["x"] = {1, 3, 4, 5};
    expectedVarToStmtNum["y"] = {2};
    expectedVarToStmtNum["w"] = {3, 4, 6};
    expectedVarToStmtNum["num1"] = {8};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    expectedVarToProcName["x"] = {"simple"};
    expectedVarToProcName["y"] = {"simple"};
    expectedVarToProcName["w"] = {"simple"};
    expectedVarToProcName["num1"] = {"simple"};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}

TEST_CASE("ModifiesExtractor with parser - if in while node") {
    string input =
        "procedure simple {"
        "read x;"
        "read y;"
        "while (x < y) {"
        "if (x == y) then {"
        "x = y + 1;"
        "} else { read w; }"
        "print z;"
        "}"
        "read num1;"
        "}";

    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::MODIFIES);
    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
    expectedVarToStmtNum["x"] = {1, 3, 4, 5};
    expectedVarToStmtNum["y"] = {2};
    expectedVarToStmtNum["w"] = {3, 4, 6};
    expectedVarToStmtNum["num1"] = {8};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    expectedVarToProcName["x"] = {"simple"};
    expectedVarToProcName["y"] = {"simple"};
    expectedVarToProcName["w"] = {"simple"};
    expectedVarToProcName["num1"] = {"simple"};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}

TEST_CASE("ModifiesExtractor with parser - no proc call") {
    string input =
        "procedure simple {"
        "read x;"
        "read y;"
        "}"
        "procedure simple2 {"
        "read x;"
        "}"
        "procedure simple3 {"
        "y = x + 1;"
        "}";

    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::MODIFIES);
    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
    expectedVarToStmtNum["x"] = {1, 3};
    expectedVarToStmtNum["y"] = {2, 4};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    expectedVarToProcName["x"] = {"simple", "simple2"};
    expectedVarToProcName["y"] = {"simple", "simple3"};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}

TEST_CASE("ModifiesExtractor with parser - 3 nested if statements") {
    string input =
        "procedure multipleIf {"
        "   read v;" // 1
        "   read w;" // 2
        "   if (v == 0) then {" // 3
        "       read x;" // 4
        "       if (w != v) then {" // 5
        "           read y;" // 6
        "           if (x > (y - 1)) then {" // 7
        "               print z;" // 8
        "           } else { print x; }" // 9
        "       } else { read z; }" // 10
        "   } else { print v; }" // 11
        "}";

    // extract
    PKBStorage storage{};
    MockPKBWriter mockPKB(storage);
    extractAbstraction(input, mockPKB, AbstractionType::MODIFIES);
    unordered_map<string, unordered_set<int>> expectedVarToStmtNum = {};
    expectedVarToStmtNum["v"] = {1};
    expectedVarToStmtNum["w"] = {2};
    expectedVarToStmtNum["x"] = {3, 4};
    expectedVarToStmtNum["y"] = {3, 5, 6};
    expectedVarToStmtNum["z"] = {3, 5, 10};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToStmtNum));

    unordered_map<string, unordered_set<string>> expectedVarToProcName = unordered_map<string, unordered_set<string>>();
    expectedVarToProcName["v"] = {"multipleIf"};
    expectedVarToProcName["w"] = {"multipleIf"};
    expectedVarToProcName["x"] = {"multipleIf"};
    expectedVarToProcName["y"] = {"multipleIf"};
    expectedVarToProcName["z"] = {"multipleIf"};
    REQUIRE(mockPKB.isModifiesEqual(expectedVarToProcName));
}
