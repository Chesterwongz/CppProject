#include <vector>
#include <memory>
#include <unordered_map>
#include <set>
#include "catch.hpp"
#include "sp/extractors/DesignExtractor.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/StmtListNode.h"
#include "../mocks/MockPKBWriter.h"
#include "../ast/TNodeUtils.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::unordered_map, std::set;

void extractFollows(TNode* node, MockPKBWriter &mockPKBWriter) {
    Populator populator;
    std::vector<std::unique_ptr<Extractor>> extractors;
    extractors.emplace_back(make_unique<FollowsExtractor>(&mockPKBWriter));
    populator.populate(node, extractors);
}

TEST_CASE("FollowsExtractor Simple Statement list") {
//    string input =
//        "procedure simple {"
//        "read num1;"
//        "read num2;"
//        "read num3;"
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
    MockPKBWriter mockPKB;
    extractFollows(programNode.get(), mockPKB);

    unordered_map<int, set<int>> expected = {};
    expected[1] = {2, 3};
    expected[2] = {3};
    REQUIRE(mockPKB.isFollowsEqual(expected));
}