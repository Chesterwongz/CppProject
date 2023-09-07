#include <vector>
#include <memory>
#include <map>
#include <set>
#include <iostream>
#include "sp/extractors/DesignExtractor.h"
#include "catch.hpp"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/StmtListNode.h"
#include "sp/ast/statements/ReadNode.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::map, std::set;

map<int, set<int>> getFollowsMap(TNode *node) {
    DesignExtractor designExtractor;
    designExtractor.extract(node);
    return designExtractor.getFollowsMap();
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

TEST_CASE("FollowsExtractor Simple Statement list") {
    unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
    unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
    unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
    unique_ptr<ReadNode> read1 = make_unique<ReadNode>(1);
    unique_ptr<ReadNode> read2 = make_unique<ReadNode>(2);
    unique_ptr<ReadNode> read3 = make_unique<ReadNode>(3);
    stmtListNode->addChild(std::move(read1));
    stmtListNode->addChild(std::move(read2));
    stmtListNode->addChild(std::move(read3));
    procNode->addChild(std::move(stmtListNode));
    programNode->addChild(std::move(procNode));
    map<int, set<int>> res = getFollowsMap(programNode.get());
    printFollowsMap(res);
    REQUIRE(res.size() == 2);
    REQUIRE(res[1] == set<int>{2, 3});
    REQUIRE(res[2] == set<int>{3});
//    string input =
//        "procedure simple {"
//        "read num1;"
//        "read num2;"
//        "}";

}