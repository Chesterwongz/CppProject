#include "NextExtractor.h"

NextExtractor::NextExtractor(PKBWriter& pkbWriter) : Extractor(pkbWriter) {}

void NextExtractor::addNext(int from, int to) {
  if (to != common::CFG_END_STMT_NUM) {
    pkbWriter.addNext(from, to);
  }
}

void NextExtractor::visitProcedure(const ProcNode& node) {
  stmtListStates.emplace_back(StmtListState{common::INVALID_STMT_NUM});
}

void NextExtractor::addEdgesToLine(int toLine) {
  stack<int>& currLines = stmtListStates.back().prevLines;
  while (!currLines.empty()) {
    int line = currLines.top();
    addNext(line, toLine);
    currLines.pop();
  }
}

void NextExtractor::postVisitProcedure(const ProcNode& node) {
  addEdgesToLine(common::CFG_END_STMT_NUM);
  stmtListStates.pop_back();
}

void NextExtractor::processStmt(const StmtNode& node) {
  int currLine = node.getLineNum();
  addEdgesToLine(currLine);
  stack<int>& currLines = stmtListStates.back().prevLines;
  currLines.push(currLine);
}

void NextExtractor::visitAssign(const AssignNode& node) { processStmt(node); }

void NextExtractor::visitCall(const CallNode& node) { processStmt(node); }

void NextExtractor::visitPrint(const PrintNode& node) { processStmt(node); }

void NextExtractor::visitRead(const ReadNode& node) { processStmt(node); }

void NextExtractor::visitIf(const IfNode& node) {
  addEdgesToLine(node.getLineNum());
  stmtListStates.emplace_back(StmtListState{node.getLineNum(), true});
}

void NextExtractor::visitWhile(const WhileNode& node) {
  processStmt(node);
  stmtListStates.emplace_back(StmtListState{node.getLineNum()});
}

void NextExtractor::postVisitIf(const IfNode& node) {
  StmtListState curr = stmtListStates.back();
  stmtListStates.pop_back();
  StmtListState& prev = stmtListStates.back();
  transferLines(curr.prevLines, prev.prevLines);
}

void NextExtractor::postVisitWhile(const WhileNode& node) {
  addEdgesToLine(node.getLineNum());
  stmtListStates.pop_back();
}

void NextExtractor::visitStmtList(const StmtListNode& node) {
  StmtListState& curr = stmtListStates.back();
  if (curr.decisionLine == common::INVALID_STMT_NUM) return;

  addNext(curr.decisionLine, node.getStartLineNum());
}

void NextExtractor::postVisitStmtList(const StmtListNode& node) {
  StmtListState& curr = stmtListStates.back();
  if (!curr.hasAdditionalStmtList) return;

  curr.hasAdditionalStmtList = false;
  StmtListState& prev = stmtListStates.rbegin()[REVERSE_INDEX_ONE];
  transferLines(curr.prevLines, prev.prevLines);
}

void NextExtractor::transferLines(stack<int>& from, stack<int>& to) {
  while (!from.empty()) {
    int line = from.top();
    to.push(line);
    from.pop();
  }
}
