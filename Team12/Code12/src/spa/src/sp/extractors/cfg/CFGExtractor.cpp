#include "CFGExtractor.h"

CFGExtractor::CFGExtractor(PKBWriter& pkbWriter) : Extractor(pkbWriter) {}

void CFGExtractor::visitProcedure(const ProcNode& node) {
    stmtListStates.emplace_back(StmtListState{common::INVALID_STMT_NUM});
    cfg = std::make_unique<CFG>();
}

void CFGExtractor::addEdgesForCurrLines(int toLine) {
    stack<int>& currLines = stmtListStates.back().lineNums;
    while (!currLines.empty()) {
        int line = currLines.top();
        cfg->addEdge(line, toLine);
        currLines.pop();
    }
}

void CFGExtractor::postVisitProcedure(const ProcNode& node) {
    addEdgesForCurrLines(common::CFG_END_STMT_NUM);
    stmtListStates.pop_back();

    string procName = node.getValue();
    pkbWriter.setCFG(procName, std::move(cfg));
}

void CFGExtractor::processStmt(const StmtNode& node) {
    int currLine = node.getLineNum();
    addEdgesForCurrLines(currLine);
    stack<int>& currLines = stmtListStates.back().lineNums;
    currLines.push(currLine);
}

void CFGExtractor::visitAssign(const AssignNode& node) {
    processStmt(node);
}

void CFGExtractor::visitCall(const CallNode& node) {
    processStmt(node);
}

void CFGExtractor::visitPrint(const PrintNode& node) {
    processStmt(node);
}

void CFGExtractor::visitRead(const ReadNode& node) {
    processStmt(node);
}

void CFGExtractor::visitIf(const IfNode& node) {
    processStmt(node);
    stmtListStates.emplace_back(StmtListState{node.getLineNum(), true});
}

void CFGExtractor::visitWhile(const WhileNode& node) {
    processStmt(node);
    stmtListStates.emplace_back(StmtListState{node.getLineNum()});
}

void CFGExtractor::postVisitIf(const IfNode& node) {
    StmtListState curr = stmtListStates.back();
    stmtListStates.pop_back();
    StmtListState& prev = stmtListStates.back();
    transferLines(curr.lineNums, prev.lineNums);
}

void CFGExtractor::postVisitWhile(const WhileNode& node) {
    addEdgesForCurrLines(node.getLineNum());
    stmtListStates.pop_back();
}

void CFGExtractor::visitStmtList(const StmtListNode &node) {
    StmtListState& curr = stmtListStates.back();
    if (curr.decisionLine == common::INVALID_STMT_NUM) return;

    cfg->addEdge(curr.decisionLine, node.getStartLineNum());
}

void CFGExtractor::postVisitStmtList(const StmtListNode& node) {
    StmtListState& curr = stmtListStates.back();
    if (!curr.hasAdditionalStmtList) return;

    curr.hasAdditionalStmtList = false;
    StmtListState& prev = stmtListStates.rbegin()[REVERSE_INDEX_ONE];
    transferLines(curr.lineNums, prev.lineNums);
}

void CFGExtractor::transferLines(stack<int>& from, stack<int>& to) {
    while (!from.empty()) {
        int line = from.top();
        to.push(line);
        from.pop();
    }
}
