#pragma once

#include <map>
#include <set>
#include <stack>
#include <vector>
#include "Extractor.h"
#include "sp/ast/statements/AssignNode.h"
#include "sp/ast/statements/CallNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/PrintNode.h"
#include "sp/ast/statements/ReadNode.h"
#include "sp/ast/statements/StmtNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/ast/StmtListNode.h"

class FollowsExtractor : public Extractor {
private:
    // temp storage for testing
    // TODO: change to use PkbWriter
    std::map<int, std::set<int>> followsMap;
    // each vector element is a nesting block, e.g. proc, if, while {}
    std::stack<std::vector<int>> nestingBlocksStack;
    void processFollows(const StmtNode *node);

public:
    FollowsExtractor(); // TODO: remove this constructor after pkb integration
    explicit FollowsExtractor(PkbWriter *pkbWriter);
    void visitAssign(const AssignNode *node) override;
    void visitCall(const CallNode *node) override;
    void visitIf(const IfNode *node) override;
    void visitPrint(const PrintNode *node) override;
    void visitRead(const ReadNode *node) override;
    void visitWhile(const WhileNode *node) override;
    void visitStmtList(const StmtListNode *node) override;
    void postVisitStmtList(const StmtListNode *node) override;

    std::map<int, std::set<int>> getFollowsMap(); // TODO: remove this method after pkb integration
};
