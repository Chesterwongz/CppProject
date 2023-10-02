#pragma once

#include <memory>
#include <stack>
#include <vector>
#include "common/cfg/CFG.h"
#include "common/Constants.h"
#include "sp/extractors/Extractor.h"
#include "sp/ast/statements/AssignNode.h"
#include "sp/ast/statements/CallNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/PrintNode.h"
#include "sp/ast/statements/ReadNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/StmtListNode.h"


using std::unique_ptr, std::stack, std::vector;

struct StmtListState {
    int decisionLine;
    bool hasAdditionalStmtList = false;
    stack<int> lineNums = stack<int>();
};

class CFGExtractor : public Extractor {
private:
    vector<StmtListState> stmtListStates;
    unique_ptr<CFG> cfg;
    void processStmt(const StmtNode& node);
    void addEdges(stack<int>& fromLines, int toLine);
    static void transferLines(stack<int>& from, stack<int>& to);

public:
    static constexpr int REVERSE_INDEX_ONE = 1;
    explicit CFGExtractor(PKBWriter& pkbWriter);
    void visitProcedure(const ProcNode& node) override;
    void postVisitProcedure(const ProcNode& node) override;

    void visitIf(const IfNode& node) override;
    void postVisitIf(const IfNode& node) override;

    void visitWhile(const WhileNode& node) override;
    void postVisitWhile(const WhileNode& node) override;

    void visitStmtList(const StmtListNode& node) override;
    void postVisitStmtList(const StmtListNode& node) override;

    void visitAssign(const AssignNode& node) override;
    void visitCall(const CallNode& node) override;
    void visitPrint(const PrintNode& node) override;
    void visitRead(const ReadNode& node) override;
};

