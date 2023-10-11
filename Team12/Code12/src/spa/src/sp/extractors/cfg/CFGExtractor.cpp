#include "CFGExtractor.h"

CFGExtractor::CFGExtractor(PKBWriter& pkbWriter) : Extractor(pkbWriter) {}

void CFGExtractor::addNext(int from, int to) {
  cfg->addEdge(from, to);
  if (to != common::CFG_END_STMT_NUM) {
    pkbWriter.addNext(from, to);
  }
}

void CFGExtractor::visitProcedure(const ProcNode& node) {
  stmtListStates.emplace_back(StmtListState{common::INVALID_STMT_NUM});
  cfg = std::make_unique<CFG>();
}

void CFGExtractor::addEdgesToLine(int toLine) {
  stack<int>& currLines = stmtListStates.back().prevLines;
  while (!currLines.empty()) {
    int line = currLines.top();
    addNext(line, toLine);
    currLines.pop();
  }
}

void CFGExtractor::postVisitProcedure(const ProcNode& node) {
  addEdgesToLine(common::CFG_END_STMT_NUM);
  stmtListStates.pop_back();

  string procName = node.getValue();
  pkbWriter.setCFG(procName, std::move(cfg));
}

void CFGExtractor::processStmt(const StmtNode& node) {
  int currLine = node.getLineNum();
  addEdgesToLine(currLine);
  stack<int>& currLines = stmtListStates.back().prevLines;
  currLines.push(currLine);
}

void CFGExtractor::visitAssign(const AssignNode& node) { processStmt(node); }

void CFGExtractor::visitCall(const CallNode& node) { processStmt(node); }

void CFGExtractor::visitPrint(const PrintNode& node) { processStmt(node); }

void CFGExtractor::visitRead(const ReadNode& node) { processStmt(node); }

void CFGExtractor::visitIf(const IfNode& node) {
  addEdgesToLine(node.getLineNum());
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
  transferLines(curr.prevLines, prev.prevLines);
}

void CFGExtractor::postVisitWhile(const WhileNode& node) {
  addEdgesToLine(node.getLineNum());
  stmtListStates.pop_back();
}

void CFGExtractor::visitStmtList(const StmtListNode& node) {
  StmtListState& curr = stmtListStates.back();
  if (curr.decisionLine == common::INVALID_STMT_NUM) return;

  addNext(curr.decisionLine, node.getStartLineNum());
}

void CFGExtractor::postVisitStmtList(const StmtListNode& node) {
  StmtListState& curr = stmtListStates.back();
  if (!curr.hasAdditionalStmtList) return;

  curr.hasAdditionalStmtList = false;
  StmtListState& prev = stmtListStates.rbegin()[REVERSE_INDEX_ONE];
  transferLines(curr.prevLines, prev.prevLines);
}

void CFGExtractor::transferLines(stack<int>& from, stack<int>& to) {
  while (!from.empty()) {
    int line = from.top();
    to.push(line);
    from.pop();
  }
}
