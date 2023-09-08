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

using std::unique_ptr, std::make_unique, std::vector, std::string, std::map, std::set;

map<int, set<int>> getFollowsMap(DesignExtractor* designExtractor) {
    return designExtractor->getFollowsMap();
}

void printFollowsMap(const map<int, set<int>>& followsMap) {
    for (const auto& elem : followsMap) {
        std::cout << elem.first << ": ";
        for (const auto &follows : elem.second) {
            std::cout << follows << " ";
        }
        std::cout << "\n";
    }
}

unique_ptr<ReadNode> makeReadNode(int lineNum) {
    return make_unique<ReadNode>(lineNum);
}

TEST_CASE("FollowsExtractor Simple Statement list") {
//    string input =
//        "procedure simple {"
//        "read num1;"
//        "read num2;"
//        "}";
    unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
    unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
    unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
    stmtListNode->addChild(makeReadNode(1));
    stmtListNode->addChild(makeReadNode(2));
    stmtListNode->addChild(makeReadNode(3));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));
    // extract
    DesignExtractor designExtractor;
    designExtractor.extract(programNode.get());

    // get follows map
    map<int, set<int>> res = getFollowsMap(&designExtractor);
    printFollowsMap(res);
    REQUIRE(res.size() == 2);
    REQUIRE(res[1] == set<int>{2, 3});
    REQUIRE(res[2] == set<int>{3});
}